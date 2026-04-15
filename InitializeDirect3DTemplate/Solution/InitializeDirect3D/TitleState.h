#pragma once
#include "State.h"
#include "../../Common/GameTimer.h"
#include <Windows.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wrl/client.h>
#include <string>

using Microsoft::WRL::ComPtr;

class TitleState : public State
{
public:
    TitleState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(const GameTimer& gt) override;
    bool handleEvent(MSG msg) override;

private:
    std::string			mSprite;
    std::wstring mText;

    bool  mShowText;
    float mTextEffectTime;
    bool mStartGame = false;
    bool mRequestMenu = false;
    bool mBuilt;
};


