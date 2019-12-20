#pragma once
#include "GameObject.h"

class GamePlayStatics
{
public:
	template<class T>
	static T* FindObjectOfClass();
};
