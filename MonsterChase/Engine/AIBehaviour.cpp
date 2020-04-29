#include "AIBehaviour.h"
#include "GameObject.h"
#include "GamePlayStatics.h"
#include <cmath>

AIBehaviour::AIBehaviour(GameObject* root,Behaviour type)
{
	gameObject = root;
	behaviourType = type;
}

void AIBehaviour::Start()
{

}

void AIBehaviour::Update()
{
	
}

Point2D* AIBehaviour::GetAIMovement()
{	
	Point2D* dirToMove;
	if (behaviourType == Behaviour::RandomMotion)
	{
		dirToMove = new Point2D();
		//Randomize X
		if (((double)rand() / (RAND_MAX)) < 0.5f)
		{
			dirToMove->x = 0;
		} 
		else
		{
			dirToMove->x = 1;
		}
		//Randomize Y
		if (((double)rand() / (RAND_MAX)) < 0.5f)
		{
			dirToMove->y = 0;
		}
		else
		{
			dirToMove->y = 1;
		}
		return dirToMove;
	}
	else 
	{
		dirToMove = new Point2D();
		return dirToMove;
	}
}
