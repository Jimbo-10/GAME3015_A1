#pragma once

#include "Comand.h"
#include <map>
#include <Windows.h>


class CommandQueue;

class Player
{
public:
	Player();
	void					handleEvent(UINT message, WPARAM wParam, CommandQueue& commands);
	void					handleRealtimeInput(CommandQueue& commands);
#pragma region step 1
	//static const float		PlayerSpeed;
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		GetPosition,
		ActionCount
	};
	void					assignKey(Action action, int key);
	int getAssignedKey(Action action) const;


private:
	void					initializeActions();
	static bool				isRealtimeAction(Action action);


private:
	std::map<int, Action> mKeyBinding;   // Win32 virtual key codes
	std::map<Action, Comand> mActionBinding;
#pragma endregion

};

