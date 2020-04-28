#pragma once
#include "GameObject.h"
#include "Point2D.h"
#include <string>
class Sprite : public GameObject
{
public:
	Sprite(std::wstring fileName, float posX, float posY);
	~Sprite();
};
