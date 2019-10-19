#pragma once
#include "Point2D.h"
class Monster {

public:
	char* name;
	int lifeTime;
	Point2D* position;

	Monster(int, int);
	~Monster();
	void Move(Point2D*);
};

