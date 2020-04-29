#include "Point2D.h"
#include <math.h>

Point2D::Point2D() {
	this->x = 0;
	this->y = 0;
}

//Overloaded constructor for direct input
Point2D::Point2D(float x ,float y)
{
	this->x = x;
	this->y = y;
}

float Point2D::Length()
{
	return (float)sqrt(x*x + y*y);
}

float Point2D::SquareLength()
{
	return x * x + y * y;
}

Point2D* Point2D::Normalize()
{
	Point2D* normalized = new Point2D();
	if (Length() != 0)
	{
		normalized->x = x / Length();
		normalized->y = y / Length();
	}
	return normalized;
}

