#pragma once
#include "State.h"
#include "World.h"
#include "Player.h"
#include "../../Common/GameTimer.h"
#include <Windows.h>
#include "Application.h"

class GameState : public State
{
	public:
		GameState(StateStack& stack, Context context);

		virtual void		draw() override;
		virtual bool		update(const GameTimer& gt) override;
		virtual bool handleEvent(MSG msg) override;

		bool mBuilt = false;
	private:
		World				mWorld;
		Player& mPlayer;
	
};

