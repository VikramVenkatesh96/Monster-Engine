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
	ListNode<GameObject>* iterator = GameObject::GetGlobalGameObjectList()->start;
	while (iterator != nullptr)
	{
		if (dynamic_cast<T*>(iterator->value) != nullptr)
		{
			break;
		}
		iterator = iterator->next;
	}
	if (iterator == nullptr)
	{
		return nullptr;
	}
	else
	{
		return dynamic_cast<T*>(iterator->value);
	}
}
