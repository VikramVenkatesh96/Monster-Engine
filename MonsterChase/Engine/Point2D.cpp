#include "Point2D.h"
#include <iostream>


Point2D::Point2D() {
	x = 0;
	y = 0;
}

//Overloaded constructor for direct input
Point2D::Point2D(float x ,float y)
{
	this->x = x;
	this->y = y;
}

void Point2D::PrintPoint() {
	std::cout << "(" << x << "," << y << ")";
}
