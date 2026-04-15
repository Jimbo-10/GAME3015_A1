#pragma once
#include "Component.h"
#include <vector>
#include <memory>

namespace GUI
{

    class Container : public Component
    {
    public:
        using Ptr = std::shared_ptr<Container>;
        void select(std::size_t index);

    public:
        Container();

        void pack(Component::Ptr component);

        virtual bool isSelectable() const override;

        virtual void handleEvent(MSG msg) override;

        virtual void draw() override;

    private:
        bool hasSelection() const;
        //void select(std::size_t index);
        void selectNext();
        void selectPrevious();

    private:
        std::vector<Component::Ptr> mChildren;
        int mSelectedChild;
    };

} // namespace GUI

