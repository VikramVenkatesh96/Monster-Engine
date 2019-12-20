#include "GameObject.h"

GameObject::GameObject(Point2D position)
{
	this->position = position;
}

void GameObject::Translate(Point2D toPosition) {
	
	this->position = toPosition;
}
