#include "Monster.h"
#include "MemoryManager.h"
#include<iostream>

Monster::Monster(int GRIDX, int GRIDY)
{
	name = (char*)MemoryManager::AllocateMem(sizeof(char));
	lifeTime = rand() % 15;
#pragma warning(disable : 4244)
	position = new Point2D(static_cast <float>(rand() % GRIDX), static_cast <float>(rand() % GRIDY));
}

void Monster::Move(Point2D* toGo) {
	*position = *position + *toGo;
	lifeTime--;
}

Monster::~Monster() {
	MemoryManager::FreeMem(name);
	delete position;
}

