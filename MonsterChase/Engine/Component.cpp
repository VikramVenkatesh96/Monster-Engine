#include "Component.h"
#include "GameObject.h"
#include <iostream>
Component::Component(SmartPtr<GameObject> root):
	gameObject(root)
{

}
void Component::Start()
{

}
void Component::Update()
{

}
