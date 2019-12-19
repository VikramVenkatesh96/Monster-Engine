#include "Controller.h"
#include "Input.h"
#include <iostream>
Controller::Controller(GameObject * root,ControllerType type)
{
	controllerType = type;
}
void Controller::Start()
{
	std::cout << "Controller Registered";
}

void Controller::Update()
{
	if (controllerType == ControllerType::Player)
	{
		Input* inputComponent = gameObject->GetComponent<Input>();
		if (inputComponent)
		{
			gameObject->position->x = gameObject->position->x + inputComponent->GetAxis()->x;
			gameObject->position->y = gameObject->position->y + inputComponent->GetAxis()->y;
		}
		else
		{
			std::cout << "No Input Component Available";
		}
	}
	else if (controllerType == ControllerType::AI)
	{
		//getAIcomponent
	}
}