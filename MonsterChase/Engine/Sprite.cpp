#include "Sprite.h"
#include "RigidBody2D.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "Controller.h"

Sprite::Sprite(std::wstring fileName, float posX, float posY)
{
	position->x = posX;
	position->y = posY;
	this->AddComponent(new Input(this));
	this->AddComponent(new Controller(this, ControllerType::Player,50.0f));
	this->AddComponent(new RigidBody2D(this, 10.0f, true, true));
	this->AddComponent(new SpriteRenderer(this,fileName));
}


Sprite::~Sprite()
{
}



