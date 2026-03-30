#pragma once

#include "Category.h"
#include <functional>
#include <cassert>


class SceneNode;

using Time = float;

struct Comand
{
	Comand();

	std::function<void(SceneNode&, Time)>	action;
	unsigned int								category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, Time)> derivedAction(Function fn)
{
	return [=](SceneNode& node, float dt)
		{
			// Check if cast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// Downcast node and invoke function on it
			fn(static_cast<GameObject&>(node), dt);
		};
}