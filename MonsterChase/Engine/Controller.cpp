#include "Controller.h"
#include "GameObject.h"
#include "Input.h"
#include "AIBehaviour.h"
#include <iostream>

Controller::Controller(GameObject * root,ControllerType type)
{	
	gameObject = root;
	controllerType = type;
}
void Controller::Start()
{
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
			std::cout << "No Input Component Available"<< std::endl;
		}
	}
	else if (controllerType == ControllerType::AI)
	{
		AIBehaviour* behaviour = gameObject->GetComponent<AIBehaviour>();
		if (behaviour)
		{
			*gameObject->position = *gameObject->position + *behaviour->GetAIMovement();
		}
		else
		{
			std::cout << "No AI behaviour component found"<< std::endl;
		}
	}
}