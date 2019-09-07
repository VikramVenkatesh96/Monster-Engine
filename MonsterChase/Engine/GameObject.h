#pragma once
#include "Point2D.h" 

class GameObject
{
	
public:
	
	Point2D position;
	
	GameObject(Point2D);
	void Translate(Point2D);
};

