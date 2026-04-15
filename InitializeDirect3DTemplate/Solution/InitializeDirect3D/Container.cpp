#include "Container.h"

namespace GUI
{

    Container::Container()
        : mChildren()
        , mSelectedChild(-1)
    {
    }

    void Container::pack(Component::Ptr component)
    {
        mChildren.push_back(component);

        if (!hasSelection() && component->isSelectable())
            select(mChildren.size() - 1);
    }

    bool Container::isSelectable() const
    {
        return false; // container itself is not selectable
    }

    // ----------------------------------------------------
    // INPUT HANDLING (Win32 MSG instead of SFML events)
    // ----------------------------------------------------
    void Container::handleEvent(MSG msg)
    {
        if (hasSelection() && mChildren[mSelectedChild]->isActive())
        {
            mChildren[mSelectedChild]->handleEvent(msg);
            return;
        }

        if (msg.message == WM_KEYDOWN)
        {
            switch (msg.wParam)
            {
            case VK_UP:
                selectPrevious();
                break;

            case VK_DOWN:
                selectNext();
                break;

            case VK_RETURN:
            case VK_SPACE:
                if (hasSelection())
                    mChildren[mSelectedChild]->activate();
                break;
            }
        }
    }

    // ----------------------------------------------------
    // DRAW (DirectX will handle actual rendering later)
    // ----------------------------------------------------
    void Container::draw()
    {
        for (auto& child : mChildren)
            child->draw();
    }

    // ----------------------------------------------------
    // SELECTION LOGIC
    // ----------------------------------------------------
    bool Container::hasSelection() const
    {
        return mSelectedChild >= 0;
    }

    void Container::select(std::size_t index)
    {
        if (mChildren[index]->isSelectable())
        {
            if (hasSelection())
                mChildren[mSelectedChild]->deselect();

            mChildren[index]->select();
            mSelectedChild = index;
        }
    }

    void Container::selectNext()
    {
        if (!hasSelection())
            return;

        int next = mSelectedChild;

        do
        {
            next = (next + 1) % mChildren.size();
        } while (!mChildren[next]->isSelectable());

        select(next);
    }

    void Container::selectPrevious()
    {
        if (!hasSelection())
            return;

        int prev = mSelectedChild;

        do
        {
            prev = (prev + mChildren.size() - 1) % mChildren.size();
        } while (!mChildren[prev]->isSelectable());

        select(prev);
    }

} // namespace GUI