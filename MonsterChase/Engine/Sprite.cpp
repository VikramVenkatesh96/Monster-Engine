#include "Sprite.h"
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
	this->AddComponent(new Input(SmartPtr<GameObject>(this)));
	this->AddComponent(new Controller(SmartPtr<GameObject>(this), ControllerType::Player, 50.0f));
	this->AddComponent(new RigidBody2D(SmartPtr<GameObject>(this), 10.0f, true, true));
	this->AddComponent(new SpriteRenderer(SmartPtr<GameObject>(this), fileName));
}

Sprite::~Sprite()
{
}



