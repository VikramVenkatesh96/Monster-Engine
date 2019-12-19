#include "Input.h"
#include "GameObject.h"
#include <conio.h>
#include <iostream>

Input::Input(GameObject * root)
{
	gameObject = root;
	inputAxis = new Point2D();
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
	char input = _getch();
	if (input == 'w')
	{
		inputAxis->y = 1;
		inputAxis->x = 0;
	}
	else if (input == 'a')
	{
		inputAxis->y = 0;
		inputAxis->x = -1;
	}
	else if (input == 's')
	{
		inputAxis->y = -1;
		inputAxis->x = 0;
	}
	else if (input == 'd')
	{
		inputAxis->y = 0;
		inputAxis->x = 1;
	}
	else
	{
		inputAxis->y = 0;
		inputAxis->x = 0;
	}
}
