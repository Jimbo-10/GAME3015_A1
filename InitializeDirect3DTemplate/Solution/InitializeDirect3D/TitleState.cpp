#include "TitleState.h"
#include "StateStack.h"
#include "Application.h"
#include <Windows.h>

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
    , mShowText(true)
    , mTextEffectTime(0.0f)
    , mBuilt(false)
{
}

void TitleState::draw()
{
    if (!mBuilt) return;
}

bool TitleState::update(const GameTimer& gt)
{
    mTextEffectTime += gt.DeltaTime();

    if (mTextEffectTime >= 0.5f)
    {
        mShowText = !mShowText;
        mTextEffectTime = 0.0f;
    }

    if (!mBuilt)
    {
        auto* game = getContext().game;

        game->getRenderItems().clear();
        game->getOpaqueRenderItems().clear();

        auto& mats = game->getMaterials();
        auto& geos = game->getGeometries();

        auto matIt = mats.find("title");
        auto geoIt = geos.find("boxGeo");

        if (matIt == mats.end() || geoIt == geos.end())
        {
            return true;
        }

        auto render = std::make_unique<RenderItem>();

        XMStoreFloat4x4(
            &render->World,
            XMMatrixScaling(0.9f, 0.7f, 1.0f) *
            XMMatrixTranslation(0.0f, -1.0f, 0.5f)
        );

        render->ObjCBIndex = game->getRenderItems().size();
        render->Mat = matIt->second.get();
        render->Geo = geoIt->second.get();
        render->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

        render->IndexCount = render->Geo->DrawArgs["quad"].IndexCount;
        render->StartIndexLocation = render->Geo->DrawArgs["quad"].StartIndexLocation;
        render->BaseVertexLocation = render->Geo->DrawArgs["quad"].BaseVertexLocation;

        game->getRenderItems().push_back(std::move(render));

        for (auto& e : game->getRenderItems())
            e->NumFramesDirty = 3;

        auto& all = game->getRenderItems();
        auto& opaque = game->getOpaqueRenderItems();

        opaque.clear();
        for (auto& e : all)
            opaque.push_back(e.get());

        game->mNeedRebuild = true;

        mBuilt = true;
    }

    return true;
}

bool TitleState::handleEvent(MSG msg)
{
    /*if (msg.message == WM_KEYDOWN && msg.wParam == VK_SPACE)
    {
        OutputDebugStringA("TITLE -> GAME\n");

        requestStateClear();
        requestStackPush(States::Game);

        return false;
    }*/
    
    static bool spacePressed = false;

    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        if (!spacePressed)
        {
            spacePressed = true;

            OutputDebugStringA("SPACE PRESSED ONCE\n");

            requestStackPop();
            requestStackPush(States::Menu);
        }
    }
    else
    {
        spacePressed = false;
    }

    return true;
}
