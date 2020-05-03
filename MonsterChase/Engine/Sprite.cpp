#include "Sprite.h"
#include "Component.h"
#include "RigidBody2D.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Controller.h"

Sprite::Sprite()
{
}
Sprite::Sprite(std::wstring fileName, float posX, float posY):
	fileName(fileName)
{
	position->x = posX;
	position->y = posY; 
}

void Sprite::Initialize()
{
	this->AddComponent(SmartPtr<Component>(new Input(*this)));
	this->AddComponent(SmartPtr<Component>(new Controller(*this, ControllerType::Player, 50.0f)));
	this->AddComponent(SmartPtr<Component>(new RigidBody2D(*this, 10.0f, true, true)));
	this->AddComponent(SmartPtr<Component>(new SpriteRenderer(*this, fileName)));
}

Sprite::~Sprite()
{
}



