#include "StateStack.h"
#include "Application.h"
#include <cassert>
#include <stdexcept>
#include <typeinfo>
#include <string>

StateStack::StateStack(State::Context context)
    : mStack()
    , mPendingList()
    , mContext(context)
    , mFactories()
{
    if (!context.game)
        OutputDebugStringA("ERROR: game is null in context\n");
}

void StateStack::update(const GameTimer& gt)
{
    //applyPendingChanges();

    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(gt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    OutputDebugStringA(typeid(*mStack.back()).name());
    OutputDebugStringA("\n");
    for (State::Ptr& state : mStack)
        state->draw();
}

void StateStack::handleEvent(MSG msg)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        OutputDebugStringA("StateStack passing event\n");
        OutputDebugStringA(typeid(**itr).name());

        if (!(*itr)->handleEvent(msg))
            break;
    }

    applyPendingChanges();

}

void StateStack::pushState(States::ID stateID)
{
    mPendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    //assert(found != mFactories.end());
    if (found == mFactories.end())
    {
        throw std::runtime_error("State not registered.");
    }
    return found->second();
}

void StateStack::applyPendingChanges()
{
    for (PendingChange change : mPendingList)
    {
        switch (change.action)
        {
        case Push:
            mContext.game->getRenderItems().clear();
            mContext.game->getOpaqueRenderItems().clear();
            mStack.push_back(createState(change.stateID));
            break;

        case Pop:
            mStack.pop_back();
            break;

        case Clear:
            mStack.clear();
            break;
        }
    }
    OutputDebugStringA(("Pending size: " + std::to_string(mPendingList.size()) + "\n").c_str());
    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
    : action(action)
    , stateID(stateID)
{
}