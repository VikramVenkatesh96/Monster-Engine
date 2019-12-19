#include "Monster.h"
#include "MemoryManager.h"
#include<iostream>

Monster::Monster()
{
}
Monster::Monster(int GRIDX, int GRIDY)
{	
	position->x = static_cast <float>(rand() % GRIDX);
	position->y = static_cast <float>(rand() % GRIDY);
	name =(char*)MemoryManager::AllocateMem(sizeof(char));
	lifeTime = rand() % 15;
}

void Monster::Move(Point2D* toGo) {
	*position = *position + *toGo;
	lifeTime--;
}

Monster::~Monster() {
	MemoryManager::FreeMem(name);
}
