#include "CommandQueue.h"
#include "SceneNode.h"


void CommandQueue::push(const Comand& command)
{
	mQueue.push(command);
}

Comand CommandQueue::pop()
{
	Comand command = mQueue.front();
	mQueue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}