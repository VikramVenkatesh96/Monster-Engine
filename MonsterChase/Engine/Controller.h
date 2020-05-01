#pragma once
#include "Component.h"
enum class ControllerType { Player, AI };

class Controller: public Component
{
public:
	Controller(SmartPtr<GameObject>, ControllerType, float maxForce);
	virtual void Start() override;
	virtual void Update() override;
private:
	ControllerType controllerType;
	float maxForceMultiplier;
};

