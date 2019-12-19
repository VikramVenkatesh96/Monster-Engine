#pragma once
#include "Component.h"
#include <functional>

class Script :public Component
{
public:
	Script(GameObject*, std::function<void()>, std::function<void()>);
	virtual void Start();
	virtual void Update();
private:
	std::function<void()> startFunc;
	std::function<void()> updateFunc;
};

