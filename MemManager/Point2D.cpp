#include "Point2D.h"
#include <iostream>

Point2D::Point2D() {
	this->x = 0;
	this->y = 0;
}

//Overloaded constructor for direct input
Point2D::Point2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

const float Point2D::X()
{
	return x;
}

const float Point2D::Y()
{
	return y;
}

float Point2D::Length()
{
	return sqrt(x * x + y * y);
}

Point2D* Point2D::Normalize()
{
	Point2D* normalized = new Point2D();
	normalized->x = x / Length();
	normalized->y = y / Length();
	return normalized;
}

void Point2D::PrintPoint() {
	std::cout << "(" << x << "," << y << ")";
}
