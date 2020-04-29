#pragma once
#include "Script.h"

class PlayerMovement : public Script
{
public:
	PlayerMovement(GameObject*);
	~PlayerMovement();
protected:
	void Start() override;
	void Update() override;
};

