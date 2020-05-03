#include "Controller.h"
#include "GameObject.h"
#include "Input.h"
#include "AIBehaviour.h"
#include "RigidBody2D.h"

Controller::Controller(GameObject& root,ControllerType type, float maxForce):
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
		SmartPtr<Input> inputComponent = gameObject.GetComponent<Input>();
		SmartPtr<RigidBody2D> rb = gameObject.GetComponent<RigidBody2D>();
		if (inputComponent)
		{
			if (inputComponent->GetAxis()->SquareLength() != 0)
			{
				rb->AddForce(*inputComponent->GetAxis() * maxForceMultiplier);
			}
		}
		else
		{
			//No input Component
		}
	}
	else if (controllerType == ControllerType::AI)
	{
		SmartPtr<AIBehaviour> behaviour = gameObject.GetComponent<AIBehaviour>();
		if (behaviour)
		{
			*gameObject.position = *gameObject.position + *behaviour->GetAIMovement();
		}
		else
		{
			//No AI behaviour
		}
	}
}