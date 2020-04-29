#pragma once
#include "Component.h"
#include <functional>

class Script :public Component
{
public:
	Script(GameObject*);
	//(OLD)
	//Script(GameObject*, std::function<void()>, std::function<void()>);
protected:
	virtual void Start();
	virtual void Update();

	//(OLD)Used function to directly run from Script start and update
//private:
//	std::function<void()> startFunc;
//	std::function<void()> updateFunc;
};

