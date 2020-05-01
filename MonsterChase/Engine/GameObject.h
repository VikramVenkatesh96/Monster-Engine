#pragma once
#include "Point2D.h"
#include "Pointers.h"
#include <vector>

class Component;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();
	virtual void Initialize();
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

public:
	Point2D* position;
private:
	std::vector<Component*> components;

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

