#include "Point2D.h"
#include <iostream>


Point2D::Point2D() {
	x = 0;
	y = 0;
}

//Overloaded constructor for direct input
Point2D::Point2D(int x ,int y)
{
	this->x = x;
	this->y = y;
}


