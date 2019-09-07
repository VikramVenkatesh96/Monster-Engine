#pragma once
class Point2D
{

public:
	int x;
	int y;
	Point2D();
	Point2D(int,int);
	void PrintPoint();

	Point2D operator + (Point2D const &obj) {
		Point2D res;
		res.x = x + obj.x;
		res.y = y + obj.y;
		return res;
	}
	
	Point2D operator * (int const &c) {
		Point2D res;
		res.x = x * c;
		res.y = y * c;
		return res;
	}

	bool operator == (Point2D const &obj) {
		if ((x == obj.x) && (y == obj.y)) 
			return true;
		else
			return false;
	}

	bool operator < (Point2D const &obj) {
		if ((x < obj.x) && (y < obj.x))
			return true;
		else
			return false;
	}

};

