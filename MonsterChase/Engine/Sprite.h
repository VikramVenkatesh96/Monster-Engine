#pragma once
#include "GameObject.h"
#include "Point2D.h"
#include <string>
class Sprite : public GameObject
{
public:
	Sprite();
	Sprite(std::wstring fileName, float posX, float posY);
	~Sprite();
	void Initialize() override;
private:
	std::wstring fileName;
};
