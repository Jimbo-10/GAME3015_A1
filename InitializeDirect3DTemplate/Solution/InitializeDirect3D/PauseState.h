#pragma once
#include "State.h"
#include "Container.h"
#include "../../Common/GameTimer.h"
#include <memory>
#include <Windows.h>

class PauseState : public State
{
public:
    PauseState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(const GameTimer& gt);
    virtual bool handleEvent(MSG msg) override;

private:
    // In DirectX you don’t use sf::Sprite / sf::Text
    // These will be handled via your renderer (SpriteBatch / SpriteFont later)

    /*void drawBackground();
    void drawPausedText();*/

private:
    GUI::Container mGUIContainer;
};

