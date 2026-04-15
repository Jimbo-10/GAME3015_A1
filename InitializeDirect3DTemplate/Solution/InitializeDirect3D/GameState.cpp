#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context)
    , mWorld(context.game)   
    , mPlayer(*context.player)
{
}

void GameState::draw()
{  
    mWorld.draw();   
}

bool GameState::update(const GameTimer& gt)
{
    //mWorld.update(gt);

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    if (!mBuilt)
    {
        auto* game = getContext().game;

        game->getRenderItems().clear();
        game->getOpaqueRenderItems().clear();

        mWorld.buildGameScene();

        auto& all = game->getRenderItems();
        auto& opaque = game->getOpaqueRenderItems();

        int index = 0;
        for (auto& e : all)
        {
            e->ObjCBIndex = index++;
            e->NumFramesDirty = gNumFrameResources;
            opaque.push_back(e.get());
        }

        game->mNeedRebuild = true;

        OutputDebugStringA(("GAME ALL: " + std::to_string(all.size()) + "\n").c_str());

        mBuilt = true;
    }

    mWorld.update(gt);

    return true;
}

bool GameState::handleEvent(MSG msg)
{
    //CommandQueue& commands = mWorld.getCommandQueue();
    //mPlayer.handleEvent(msg.message, msg.wParam, commands);

    //// Escape ? Pause state
    //if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
    //{
    //    requestStackPush(States::Pause);
    //}

    return true;
}