#include "Component.h"
#include "GameObject.h"
#include "MainGameLoopVariables.h"
#include<iostream>

List<GameObject>GameObject::globalGameObjectList = List<GameObject>();

GameObject::GameObject()
{
	position = new Point2D();
	components = new List<Component>();
	globalGameObjectList.Add(this);
}

GameObject::~GameObject()
{
	components->RemoveAll();
	globalGameObjectList.Remove(this);
	
}

void GameObject::Translate(Point2D toPosition) {
	
	*this->position = toPosition;
}

List<Component>* GameObject::GetAllComponents()
{
	return components;
}

void GameObject::RemoveComponent(unsigned int index)
{
	components->Remove(index);
}

void GameObject::RemoveAllComponents()
{
	components->RemoveAll();
}

//void GameObject::SetGlobalGameObjectList(List<GameObject>& gameObjects)
//{
//	 gameObjects = globalGameObjectList;
//}

List<GameObject>* GameObject::GetGlobalGameObjectList()
{
	return &globalGameObjectList;
}
