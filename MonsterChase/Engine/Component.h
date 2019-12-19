#pragma once
#include "GameObject.h"

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