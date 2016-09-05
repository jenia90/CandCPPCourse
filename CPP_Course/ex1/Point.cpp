//
// Created by jenia on 04/09/2016.
//

#include "Point.h"

Point::Point()
{
}

Point::Point(int x, int y): _x(x), _y(y)
{
}

Point::~Point()
{
}

void Point::set(int x, int y)
{
	_x = x;
	_y = y;
}

bool Point::operator==(const Point& p) const
{
	return (this->_x == p._x) && (this->_y == p._y);
}

std::istream& operator>>(std::istream& is, Point& point)
{
	std::string str;
	is >> str;
	int delimIdx = str.find(",");
	point.set(std::stoi(str.substr(0, delimIdx)), std::stoi(str.substr(delimIdx + 1, str.length() - 1)));
	return is;
}

std::string Point::toString()
{
}

