#pragma once
#include "Comand.h"
#include <queue>
class CommandQueue
{
public:
	void						push(const Comand& command);
	Comand						pop();
	bool						isEmpty() const;


private:
	std::queue<Comand>			mQueue;
};

