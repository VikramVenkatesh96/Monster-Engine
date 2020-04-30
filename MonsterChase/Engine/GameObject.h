#pragma once
#include "DataStructures.h"
#include "Point2D.h"
#include <vector>

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

	std::vector<Component*>* GetAllComponents();
	void RemoveComponent(unsigned int);
	void RemoveAllComponents();
	void Inspector();
	//static void SetGlobalGameObjectList(List<GameObject>&);
	static std::vector<GameObject*>* GetGlobalGameObjectList();

private:
	std::vector<Component*> components;
	static std::vector<GameObject*> gameObjects;

};

template<class T>
void GameObject::AddComponent(T* component)
{
	components.push_back(component);
}

template<class T>
T* GameObject::GetComponent()
{
	for (unsigned int i = 0; i < components.size(); ++i)
	{
		if (dynamic_cast<T*>(components.at(i)) != nullptr)
		{
			return dynamic_cast<T*>(components.at(i));
		}
	}
	return nullptr;
}
