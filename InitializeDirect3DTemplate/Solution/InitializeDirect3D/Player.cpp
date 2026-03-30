#include "Player.h"
#include "CommandQueue.h"
#include "Aircraft.h"

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

#include <DirectXMath.h>

using namespace DirectX;


struct AircraftMover
{
	/*AircraftMover(float vx, float vy, float vz) :
		velocity(vx, vy, vz)
	{
	}
	void operator() (SceneNode& node, float dt) const
	{
		Boulder& aircraft = static_cast<Boulder&>(node);
		aircraft.accelerate(velocity);
	}
	XMFLOAT3 velocity;*/

	XMFLOAT3 velocity;

	AircraftMover(float vx, float vy, float vz)
		: velocity(vx, vy, vz)
	{
	}

	void operator()(Boulder& boulder, float dt) const
	{
		boulder.accelerate(velocity);
	}
};

Player::Player()
{
	// Set initial key bindings
	mKeyBinding[VK_LEFT] = MoveLeft;
	mKeyBinding[VK_RIGHT] = MoveRight;
	mKeyBinding[VK_UP] = MoveUp;
	mKeyBinding[VK_DOWN] = MoveDown;
	//mKeyBinding[sf::Keyboard::P] = GetPosition;

	// Set initial action bindings
	initializeActions();

	// Assign all categories to player's aircraft
	for (auto& pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::handleEvent(UINT message, WPARAM wParam, CommandQueue& commands)
{
	if (message == WM_KEYDOWN)
	{
		auto found = mKeyBinding.find(static_cast<int>(wParam));

		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		{
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
	// Traverse all assigned keys and check if they are pressed
	for (const auto& pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if ((GetAsyncKeyState(pair.first) & 0x8000) && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, int key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

int Player::getAssignedKey(Action action) const
{
	for (const auto& pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return 0; // no key assigned
}

void Player::initializeActions()
{
	const float playerSpeed = 10.f;

	mActionBinding[MoveLeft].action = derivedAction<Boulder>(AircraftMover(-playerSpeed, 0.f, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Boulder>(AircraftMover(+playerSpeed, 0.f, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Boulder>(AircraftMover(0.f, -playerSpeed, 0.f));
	mActionBinding[MoveDown].action = derivedAction<Boulder>(AircraftMover(0.f, +playerSpeed, 0.f));
	mActionBinding[GetPosition].action = [](SceneNode& s, float dt) {
		//std::cout << s.getPosition().x << "," << s.getPosition().y << "\n";
		};
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case MoveDown:
	case MoveUp:
		return true;

	default:
		return false;
	}
}

#pragma endregion