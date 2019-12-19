#pragma once
#include "Component.h"
#include "GameObject.h"
class Input:public Component
{
public:
	Input(GameObject *);
	virtual void Start() override;
	virtual void Update() override;
	Point2D* GetAxis();
private:
	Point2D* inputAxis;
};

