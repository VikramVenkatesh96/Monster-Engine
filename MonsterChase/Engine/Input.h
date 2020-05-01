#pragma once
#include "Component.h"
#include "Point2D.h"

class Input:public Component
{
public:
	Input(SmartPtr<GameObject>);
	~Input();
	virtual void Start() override;
	virtual void Update() override;
	Point2D* GetAxis();
private:
	Point2D* inputAxis;
};

