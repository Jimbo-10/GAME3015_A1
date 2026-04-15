#include "MenuState.h"
#include "Application.h"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context)
    , mOptionIndex(0)
    , mBuilt(false)
{
}

bool MenuState::update(const GameTimer& gt)
{
    if (!mBuilt)
    {
        mOptionIndex = 0;
        mGUIContainer = nullptr;
        auto* game = getContext().game;

        auto& all = game->getRenderItems();
        auto& opaque = game->getOpaqueRenderItems();

        auto& materials = game->getMaterials();
        auto& geos = game->getGeometries();

        auto matIt = materials.find("bricks");
        auto geoIt = geos.find("boxGeo");

        if (matIt == materials.end() || geoIt == geos.end())
        {
            OutputDebugStringA("Missing materials or geometry\n");
            return true;
        }

        auto render = std::make_unique<RenderItem>();

        XMStoreFloat4x4(
            &render->World,
            XMMatrixScaling(0.9f, 0.7f, 1.0f) *
            XMMatrixTranslation(0.0f, -1.0f, 0.5f)
        );


        render->NumFramesDirty = 3;

        render->ObjCBIndex = game->getRenderItems().size();
        render->Mat = matIt->second.get();
        render->Geo = geoIt->second.get();
        render->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

        render->IndexCount = render->Geo->DrawArgs["quad"].IndexCount;
        render->StartIndexLocation = render->Geo->DrawArgs["quad"].StartIndexLocation;
        render->BaseVertexLocation = render->Geo->DrawArgs["quad"].BaseVertexLocation;

        game->getRenderItems().push_back(std::move(render));

        mGUIContainer = std::make_shared<GUI::Container>();

        auto playButton = std::make_shared<GUI::Button>(*game);
        playButton->setText("Play");
        //playButton->setPosition(0.0f, 1.0f);
        playButton->setCallback([this]()
            {
                requestStackPop();
                requestStackPush(States::Game);
            });

        auto exitButton = std::make_shared<GUI::Button>(*game);
        exitButton->setText("Exit");
        exitButton->setCallback([this]()
            {
                requestStackPop();
            });

        mGUIContainer->pack(playButton);
        mGUIContainer->pack(exitButton);
        mGUIContainer->select(0);

        int index = 0;
        for (auto& e : all)
        {
            e->ObjCBIndex = index++;
            e->NumFramesDirty = 3;
        }

        opaque.clear();

        for (auto& e : all)
        {
            opaque.push_back(e.get());
        }

        game->mNeedRebuild = true;

        mBuilt = true;
    }

    return true;
}

void MenuState::draw()
{
    if (!mBuilt) return;

    if (mGUIContainer)
        mGUIContainer->draw();
}

void MenuState::updateOptionText()
{
    for (size_t i = 0; i < mOptions.size(); i++)
    {
        if (i == mOptionIndex)
        {
            OutputDebugStringA(("> " + mOptions[i] + "\n").c_str());
        }
        else
        {
            OutputDebugStringA(("  " + mOptions[i] + "\n").c_str());
        }
    }

    OutputDebugStringA("----\n");


}

bool MenuState::handleEvent(MSG msg)
{
    /*if (msg.message != WM_KEYDOWN)
        return true;

    switch (msg.wParam)
    {
    case VK_RETURN:
        OutputDebugStringA("ENTER PRESSED\n");

        if (mGUIContainer)
            mGUIContainer->activate();

        break;

    case VK_UP:
        if (mOptionIndex > 0)
            mOptionIndex--;
        else
            mOptionIndex = mOptions.size() - 1;

        updateOptionText();

        if (mGUIContainer)
            mGUIContainer->select(mOptionIndex);

        break;

    case VK_DOWN:
        if (mOptionIndex < mOptions.size() - 1)
            mOptionIndex++;
        else
            mOptionIndex = 0;

        updateOptionText();

        if (mGUIContainer)
            mGUIContainer->select(mOptionIndex);
        break;
    }*/

    /*if (msg.message == WM_KEYDOWN)
    {
        OutputDebugStringA("KEY DOWN DETECTED\n");

        if (msg.wParam == VK_RETURN)
        {
            OutputDebugStringA("ENTER PRESSED\n");

            requestStackPop();
            requestStackPush(States::Game);

            if (mGUIContainer)
                mGUIContainer->activate();
        }
    }*/

    /*static bool enterPressed = false;
    static bool upPressed = false;
    static bool downPressed = false;

    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        if (!enterPressed)
        {
            enterPressed = true;

            OutputDebugStringA("ENTER ? GAME TRANSITION\n");

            if (mGUIContainer)
            {
                OutputDebugStringA("ACTIVATING BUTTON\n");
                mGUIContainer->activate();
            }
        }
    }
    else
    {
        enterPressed = false;
    }

    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        if (!upPressed)
        {
            upPressed = true;

            mOptionIndex = (mOptionIndex > 0)
                ? mOptionIndex - 1
                : mOptions.size() - 1;

            updateOptionText();

            if (mGUIContainer)
                mGUIContainer->select(mOptionIndex);
        }
    }
    else
    {
        upPressed = false;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        if (!downPressed)
        {
            downPressed = true;

            mOptionIndex = (mOptionIndex + 1) % mOptions.size();

            updateOptionText();

            if (mGUIContainer)
                mGUIContainer->select(mOptionIndex);
        }
    }
    else
    {
        downPressed = false;
    }*/
    if (GetAsyncKeyState(VK_RETURN) & 0x8000)
    {
        OutputDebugStringA("ENTER PRESSED\n");

        requestStackPop();
        requestStackPush(States::Game);
    }
    
    if (mGUIContainer)
        mGUIContainer->handleEvent(msg);
    
    return true;
}