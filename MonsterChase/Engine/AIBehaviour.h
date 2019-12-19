#pragma once
#include "Component.h"
#include "Point2D.h"
enum Behaviour {FollowPlayer, RandomMotion};

class AIBehaviour: public Component
{
public:
	AIBehaviour(GameObject*,Behaviour);
	virtual void Start();
	virtual void Update();
	Point2D* GetAIMovement();
private:
	Behaviour behaviourType;
};

