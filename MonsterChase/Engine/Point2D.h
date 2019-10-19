#pragma once
class Point2D
{

public:
	float x;
	float y;
	Point2D();
	Point2D(float, float);
	void PrintPoint();

	Point2D operator + (Point2D const &obj) {
		Point2D res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		return res;
	}

	Point2D operator - (Point2D const &obj) {
		Point2D res;
		res.x = x - obj.x;
		res.y = y - obj.y;
		return res;
	}

	Point2D operator * (float const &c) {
		Point2D res;
		res.x = x * c;
		res.y = y * c;
		return res;
	}

	Point2D operator / (float const &c) {
		Point2D res;
		res.x = x / c;
		res.y = y / c;
		return res;
	}

	void operator = (Point2D const &obj) {
		x = obj.x;
		y = obj.y;
	}

	Point2D operator -() const {

		return Point2D(-x, -y);
	}

	void operator += (Point2D const &obj) {

		x = x + obj.x;
		y = y + obj.y;
	}

	void operator += (float const &c) {

		x = x + c;
		y = y + c;
	}

	void operator -= (Point2D const &obj) {

		x = x - obj.x;
		y = y - obj.y;
	}

	void operator -= (float const &c) {

		x = x - c;
		y = y - c;
	}

	void operator *= (float const &c) {

		x = x * c;
		y = y * c;
	}

	void operator *= (Point2D const &obj) {

		x = x * obj.x;
		y = y * obj.y;
	}

	void operator /= (float const &c) {

		x = x / c;
		y = y / c;
	}

	void operator /= (Point2D const &obj) {

		x = x / obj.x;
		y = y / obj.y;
	}


	bool operator == (Point2D const &obj) {
		if ((x == obj.x) && (y == obj.y))
			return true;
		else
			return false;
	}

	bool operator != (Point2D const &obj) {
		if ((x != obj.x) || (y != obj.y))
			return true;
		else
			return false;
	}

	bool operator < (Point2D const &obj) {
		if ((x < obj.x) && (y < obj.y))
			return true;
		else
			return false;
	}

};
