#include "Controller.h"
#include "GameObject.h"
#include "Input.h"
#include "AIBehaviour.h"
#include "RigidBody2D.h"
#include <iostream>

Controller::Controller(SmartPtr<GameObject> root,ControllerType type, float maxForce):
	Component(root),
	maxForceMultiplier(maxForce)
{	
	controllerType = type;
}
void Controller::Start()
{
}

void Controller::Update()
{
	if (controllerType == ControllerType::Player)
	{
		Input* inputComponent = gameObject.Acquire()->GetComponent<Input>();
		RigidBody2D* rb = gameObject.Acquire()->GetComponent<RigidBody2D>();
		if (inputComponent)
		{
			if (inputComponent->GetAxis()->SquareLength() != 0)
			{
				rb->AddForce(*inputComponent->GetAxis() * maxForceMultiplier);
			}
		}
		else
		{
			std::cout << "No Input Component Available"<< std::endl;
		}
	}
	else if (controllerType == ControllerType::AI)
	{
		AIBehaviour* behaviour = gameObject.Acquire()->GetComponent<AIBehaviour>();
		if (behaviour)
		{
			*(gameObject.Acquire())->position = *(gameObject.Acquire())->position + *behaviour->GetAIMovement();
		}
		else
		{
			std::cout << "No AI behaviour component found"<< std::endl;
		}
	}
}