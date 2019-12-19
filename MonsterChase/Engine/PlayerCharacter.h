#pragma once
#include "GameObject.h"
class PlayerCharacter:public GameObject
{
public:
	PlayerCharacter();
private:
	void ScriptStart();
	void ScriptUpdate();
};

