#pragma once
#include "Component.h"

enum ControllerType {Player,AI};

class Controller: public Component
{
public:
	Controller(GameObject *, ControllerType);
	virtual void Start() override;
	virtual void Update() override;

private:
	ControllerType controllerType;
};

