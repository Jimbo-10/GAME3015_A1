#pragma once
#include <memory>
#include <Windows.h>

namespace GUI
{

    class Component
    {
    public:
        using Ptr = std::shared_ptr<Component>;

    public:
        Component();
        virtual ~Component();

        // Selection system
        virtual bool isSelectable() const = 0;

        bool isSelected() const;
        virtual void select();
        virtual void deselect();

        // Activation system (click/enter behavior)
        virtual bool isActive() const;
        virtual void activate();
        virtual void deactivate();

        // Input handling (DirectX / Win32)
        virtual void handleEvent(MSG msg) = 0;

        // Rendering (no SFML drawable anymore)
        virtual void draw() = 0;

    private:
        bool mIsSelected;
        bool mIsActive;

        // Replace sf::NonCopyable
        Component(const Component&) = delete;
        Component& operator=(const Component&) = delete;
    };

} // namespace GUI

