#include "Sprite.h"
#include "SpriteRenderer.h"

Sprite::Sprite(std::wstring fileName, float posX, float posY)
{
	position->x = posX;
	position->y = posY;
	this->AddComponent(new SpriteRenderer(this,fileName));
}


Sprite::~Sprite()
{
}



