#include "Monster.h"
#include "MemoryManager.h"
#include "Controller.h"
#include "AIBehaviour.h"
#include "Script.h"
#include<iostream>

Monster::Monster()
{
}
Monster::Monster(int GRIDX, int GRIDY)
{
	std::function<void()> startFunc = std::bind(&Monster::ScriptStart, this);
	std::function<void()> updateFunc = std::bind(&Monster::ScriptUpdate, this);
	Script* monsterScript = new Script(this, startFunc, updateFunc);
	this->AddComponent(monsterScript);
	this->AddComponent(new Controller(this,ControllerType::AI));
	this->AddComponent(new AIBehaviour(this, Behaviour::FollowPlayer));
	position->x = static_cast <float>(rand() % GRIDX);
	position->y = static_cast <float>(rand() % GRIDY);
	name =(char*)MemoryManager::AllocateMem(sizeof(char));
	lifeTime = rand() % 15;
}

void Monster::Move(Point2D* toGo) {
	*position = *position + *toGo;
	lifeTime--;
}

void Monster::ScriptStart()
{
	std::cout << "Monster initialized at: ";
	position->PrintPoint();
}

void Monster::ScriptUpdate()
{
	std::cout << "Monster at: ";
	position->PrintPoint();
}

Monster::~Monster() {
	MemoryManager::FreeMem(name);
}
