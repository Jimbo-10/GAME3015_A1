#pragma once
#include "State.h"
#include "Container.h"
#include "Button.h"
#include <vector>
#include <string>

class MenuState : public State
{
public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(const GameTimer& gt);
    virtual bool handleEvent(MSG msg);
    GUI::Container::Ptr mGUIContainer;

private:
    void updateOptionText();
    bool mBuilt;

private:
    enum OptionNames
    {
        Play,
        Exit,
    };

    std::vector<std::string> mOptions;
    std::size_t mOptionIndex;
};

