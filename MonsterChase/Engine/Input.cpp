#include "Input.h"
#include "GameObject.h"
#include "Keyboard.h"
#include "World.h"
Input::Input(SmartPtr<GameObject> root):
	Component(root)
{
	inputAxis = new Point2D();
}
Input::~Input()
{
	delete inputAxis;
}
void Input::Start()
{
}
Point2D* Input::GetAxis() 
{
	return inputAxis;
}
void Input::Update()
{
	inputAxis->y = 0;
	inputAxis->x = 0;

	if (World::GetKeyboard()->IsKeyPressed(0x57))
	{
		inputAxis->y = 1;
	}
	if (World::GetKeyboard()->IsKeyPressed(0x41))
	{
		inputAxis->x = -1;
	}
	if (World::GetKeyboard()->IsKeyPressed(0x53))
	{
		inputAxis->y = -1;
	}
	if (World::GetKeyboard()->IsKeyPressed(0x44))
	{
		inputAxis->x = 1;
	}
}
