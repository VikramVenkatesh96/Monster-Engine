#pragma once
#include "Point2D.h"
#include "GameObject.h"
class Monster: public GameObject
{

public:
	char* name;
	int lifeTime;
	
	Monster();
	Monster(int,int);
	~Monster();
	void Move(Point2D*);

private:
	void ScriptStart();
	void ScriptUpdate();
};

