#pragma once
#include "StateIdentifiers.h"
//#include "Game.h"
#include <memory>
#include <Windows.h>

class StateStack;
class Player;
class Game;
class GameTimer;

class State
{
public:
    using Ptr = std::unique_ptr<State>;

    struct Context
    {
        Context(Game* game, Player* player);

        Game* game;
        Player* player;
    };
public:
    State(StateStack& stack, Context context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(const GameTimer& gt) = 0;
    virtual bool handleEvent(MSG msg) = 0;

protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;

protected:
    StateStack* mStack;
    Context mContext;
};

