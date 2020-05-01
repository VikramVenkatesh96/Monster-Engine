#pragma once
#include "Component.h"
#include "Sheet.h"
#include <string>

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(SmartPtr<GameObject>, std::wstring fileName);
	virtual void Start() override;
	virtual void Update() override;

private:
	std::wstring fileName;
	SmartPtr<Sheet> sheet;
};

