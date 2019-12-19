#include "Component.h"
#include "GameObject.h"
#include<iostream>

List<GameObject>*GameObject::globalGameObjectList;

GameObject::GameObject()
{
	position = new Point2D();
	components = List<Component>();
	globalGameObjectList->Add(this);
}

GameObject::~GameObject()
{
	components.RemoveAll();
	globalGameObjectList->Remove(this);
	
}

void GameObject::Translate(Point2D toPosition) {
	
	*this->position = toPosition;
}

List<Component>* GameObject::GetAllComponents()
{
	return &components;
}

void GameObject::RemoveComponent(unsigned int index)
{
	components.Remove(index);
}

void GameObject::RemoveAllComponents()
{
	components.RemoveAll();
}

void GameObject::SetGlobalGameObjectList(List<GameObject>* gameObjectList)
{
	globalGameObjectList = gameObjectList;
}

List<GameObject>* GameObject::GetGlobalGameObjectList()
{
	return globalGameObjectList;
}
