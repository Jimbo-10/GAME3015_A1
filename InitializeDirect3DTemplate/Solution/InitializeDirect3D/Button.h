#pragma once
#include "Component.h"
#include "Application.h"
#include <functional>
#include <memory>
#include <string>
#include <DirectXMath.h>

class Game;
class RenderItems;

namespace GUI
{

    class Button : public Component
    {
    public:
        using Ptr = std::shared_ptr<Button>;
        using Callback = std::function<void()>;

    public:
        Button(Game& game);   

        void setCallback(Callback callback);
        void setText(const std::string& text);
        void setToggle(bool flag);

        virtual bool isSelectable() const override;

        virtual void select() override;
        virtual void deselect() override;

        virtual void activate() override;
        virtual void deactivate() override;

        virtual void handleEvent(MSG msg) override;

        virtual void draw();

    private:
        bool isMouseOver(int x, int y) const;

    private:
        Callback mCallback;
        Game& mGame;
        RenderItem* mRenderItem;

        std::string mText;

        bool mIsSelected;
        bool mIsActive;
        bool mIsToggle;

        DirectX::XMFLOAT2 mPosition;
        DirectX::XMFLOAT2 mSize;
    };

}

