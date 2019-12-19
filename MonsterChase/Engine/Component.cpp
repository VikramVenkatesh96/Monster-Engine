#include "Component.h"
#include "GameObject.h"
#include <iostream>


class Component
{
public:
    //Default constructor May cause problem
    Component();
    Component(GameObject*);
    virtual void Start();
    virtual void Update();
protected:
    GameObject* gameObject;
};

Component::Component(GameObject * root)
{
	gameObject = root;
}
void Component::Start()
{
	
}
void Component::Update()
{	
	
}
