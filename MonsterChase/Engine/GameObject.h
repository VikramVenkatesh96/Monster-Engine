#pragma once
#include "HashedString.h"
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
	void AddComponent(SmartPtr<T>);

	template <class T>
	SmartPtr<T> GetComponent();

	SmartPtr<Component> GetAtIndex(unsigned int index);

	std::vector<SmartPtr<Component>>* GetAllComponents();
	void RemoveComponent(unsigned int);
	void RemoveAllComponents();
	void Inspector();

public:
	Point2D* position;
private:
	std::vector<SmartPtr<Component>> components;

};

template<class T>
void GameObject::AddComponent(SmartPtr<T> component)
{
	components.push_back(component);
}

template<class T>
SmartPtr<T> GameObject::GetComponent()
{
	for (unsigned int i = 0; i < components.size(); ++i)
	{
		if (Pointers::Cast<T,Component>(components.at(i)))
		{
			return Pointers::Cast<T,Component>(components.at(i));
		}
	}
	return SmartPtr<T>(nullptr);
}

