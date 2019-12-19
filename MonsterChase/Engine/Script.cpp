#include "Script.h"

Script::Script(GameObject* root, std::function<void()> startFunc, std::function<void()> updateFunc)
{
	this->startFunc = startFunc;
	this->updateFunc = updateFunc;
}

void Script::Start()
{
	if (startFunc)
	{
		startFunc();
	}
}

void Script::Update()
{
	if (updateFunc)
	{
		updateFunc();
	}
}
