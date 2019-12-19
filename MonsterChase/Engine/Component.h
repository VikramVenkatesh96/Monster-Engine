#pragma once
class GameObject;

class Component
{
public:
    //Default constructor May cause problem
    Component();
    virtual void Start();
    virtual void Update();
protected:
    GameObject* gameObject;
};