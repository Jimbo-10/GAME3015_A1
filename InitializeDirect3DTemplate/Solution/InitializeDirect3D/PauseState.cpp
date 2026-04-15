#include "PauseState.h"
#include "Button.h"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context)
    , mGUIContainer()
{
    // NOTE:
    // In DirectX you don't create SFML text/sprites here anymore.
    // Rendering is handled by SpriteFont / SpriteBatch later.

    // ----------------------------------------------------
    // Create Buttons
    // ----------------------------------------------------

    /*auto returnButton = std::make_shared<GUI::Button>(
        *context.fonts,
        *context.textures
    );*/

    //returnButton->setPosition(400.f, 300.f);
    //returnButton->setText("Return");

    //returnButton->setCallback([this]()
    //    {
    //        requestStackPop();
    //    });

    ///*auto backToMenuButton = std::make_shared<GUI::Button>(
    //    *context.fonts,
    //    *context.textures
    //);*/

    //backToMenuButton->setPosition(400.f, 360.f);
    //backToMenuButton->setText("Back to menu");

    //backToMenuButton->setCallback([this]()
    //    {
    //        requestStateClear();
    //        requestStackPush(States::Menu);
    //    });

    //// Add to GUI container
    //mGUIContainer.pack(returnButton);
    //mGUIContainer.pack(backToMenuButton);
}

// ----------------------------------------------------
// DRAW (DirectX version)
// ----------------------------------------------------
void PauseState::draw()
{
    // IMPORTANT:
    // No SFML window, no views, no shapes

    auto& game = *getContext().game;

    // 1. Draw semi-transparent background (DirectX rectangle)
    //game.DrawPauseOverlay(0.5f); // you implement alpha overlay in renderer

    //// 2. Draw pause text
    //game.DrawText("Game Paused", 400.f, 200.f, 1.5f);

    // 3. Draw GUI
    mGUIContainer.draw();
}

// ----------------------------------------------------
// UPDATE
// ----------------------------------------------------
bool PauseState::update(const GameTimer& gt)
{
    // Pause state does not update game world
    return false;
}

// ----------------------------------------------------
// INPUT (Win32 MSG system)
// ----------------------------------------------------
bool PauseState::handleEvent(MSG msg)
{
    // ESC to unpause
    if (msg.message == WM_KEYDOWN && msg.wParam == VK_ESCAPE)
    {
        requestStackPop();
        return false;
    }

    // Forward input to GUI
    mGUIContainer.handleEvent(msg);

    return false;
}