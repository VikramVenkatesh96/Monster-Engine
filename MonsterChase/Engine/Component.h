#pragma once
#include "Pointers.h"
class GameObject;

class Component
{
public:
    //Default constructor May cause problem
    Component(GameObject&);
    virtual void Start();
    virtual void Update();
protected:
	GameObject& gameObject;
};