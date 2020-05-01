#pragma once
#include "GameObject.h"

class GamePlayStatics
{
public:
	template<class T>
	static T* FindObjectOfClass();
};

template<class T>
T* GamePlayStatics::FindObjectOfClass()
{
	std::vector<GameObject*>* gameObjects = GameObject::GetGlobalGameObjectList();
	for (unsigned int i = 0; i < gameObjects->size(); ++i)
	{
		if (dynamic_cast<T*>(gameObjects->at(i)) != nullptr)
		{
			return dynamic_cast<T*>(gameObjects->at(i));
		}
	}
	return nullptr;
}
