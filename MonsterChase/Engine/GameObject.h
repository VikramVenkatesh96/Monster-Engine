#pragma once
#include "DataStructures.h"
#include "Point2D.h"
class Component;

class GameObject
{
	
public:
	
	Point2D* position;
	GameObject();
	virtual ~GameObject();
	void Translate(Point2D);

	//Component Functions
	template <class T>
	void AddComponent(T*);

	template <class T>
	T* GetComponent();

	List<Component>* GetAllComponents();
	void RemoveComponent(unsigned int);
	void RemoveAllComponents();
	void Inspector();
	//static void SetGlobalGameObjectList(List<GameObject>&);
	static List<GameObject>* GetGlobalGameObjectList();

private:
	List<Component>* components;
	static List<GameObject> globalGameObjectList;
};

template<class T>
void GameObject::AddComponent(T* component)
{
	components->Add(component);
}

template<class T>
T* GameObject::GetComponent()
{
	ListNode<Component>* iterator = components->start;
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
