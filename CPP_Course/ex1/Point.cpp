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

std::string Point::toString()
{
}

