#pragma once
#include "Component.h"
#include <string>

class Sheet;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject *, std::wstring fileName);
	virtual void Start() override;
	virtual void Update() override;

private:
	std::wstring fileName;
	Sheet* sheet;
};

