#include "Button.h"
#include "Application.h"
#include "State.h"

namespace GUI
{
    Button::Button(Game& game)
        :mGame(game)
        , mCallback()
        , mText("")
        , mIsSelected(false)
        , mIsActive(false)
        , mIsToggle(false)
        , mPosition(0.f, -5.f)
        , mSize(200.f, 50.f)
        , mRenderItem(nullptr)
    {
        auto render = std::make_unique<RenderItem>();

        XMStoreFloat4x4(
            &render->World,
            XMMatrixScaling(0.3f, 0.1f, 1.0f) *
            XMMatrixTranslation(mPosition.x, mPosition.y, 0.0f)
        );

        render->NumFramesDirty = 3;
        render->ObjCBIndex = mGame.getRenderItems().size();
        render->Mat = mGame.getMaterials()["button"].get();
        render->Geo = mGame.getGeometries()["boxGeo"].get();
        render->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

        render->IndexCount = render->Geo->DrawArgs["quad"].IndexCount;
        render->StartIndexLocation = render->Geo->DrawArgs["quad"].StartIndexLocation;
        render->BaseVertexLocation = render->Geo->DrawArgs["quad"].BaseVertexLocation;

        mRenderItem = render.get();
        mGame.getRenderItems().push_back(std::move(render));
    }

    void Button::setCallback(Callback callback)
    {
        mCallback = std::move(callback);
    }

    void Button::setText(const std::string& text)
    {
        mText = text;
    }

    void Button::setToggle(bool flag)
    {
        mIsToggle = flag;
    }

    bool Button::isSelectable() const
    {
        return true;
    }

    void Button::select()
    {
        Component::select();
        mIsSelected = true;
    }

    void Button::deselect()
    {
        Component::deselect();
        mIsSelected = false;
    }

    void Button::activate()
    {
        Component::activate();
        mIsActive = true;

        if (mIsToggle)
            mIsActive = !mIsActive;

        if (mCallback)
            mCallback();

        if (!mIsToggle)
            deactivate();
    }

    void Button::deactivate()
    {
        Component::deactivate();
        mIsActive = false;
    }

    void Button::handleEvent(MSG msg)
    {
        if (msg.message == WM_LBUTTONDOWN)
        {
            int x = LOWORD(msg.lParam);
            int y = HIWORD(msg.lParam);

            if (isMouseOver(x, y))
            {
                activate();
            }
        }
    }

    bool Button::isMouseOver(int x, int y) const
    {
        return (x >= mPosition.x &&
            x <= mPosition.x + mSize.x &&
            y >= mPosition.y &&
            y <= mPosition.y + mSize.y);
    }

    void Button::draw()
    {
        if (!mRenderItem)
            return;

        auto& materials = mGame.getMaterials();

        auto button = materials.find("button");
        if (button == materials.end())
            return;

        mRenderItem->Mat = button->second.get();

        if (mIsSelected)
            mRenderItem->Mat->DiffuseAlbedo = XMFLOAT4(1.3f, 1.3f, 1.3f, 1.0f);
        else
            mRenderItem->Mat->DiffuseAlbedo = XMFLOAT4(1, 1, 1, 1);

        mRenderItem->NumFramesDirty = 3;
    }
}