#include "Monster.h"
#include "MemoryManager.h"
#include<iostream>

Monster::Monster(int GRIDX, int GRIDY)
{	name =(char*)MemoryManager::AllocateMem(sizeof(char));
	lifeTime = rand() % 15;
	position = new Point2D(rand() % GRIDX, rand() % GRIDY);
}

void Monster::Move(Point2D* toGo) {
	*position = *position + *toGo;
	lifeTime--;
}

Monster::~Monster() {
	MemoryManager::FreeMem(name);
	delete position;
}
