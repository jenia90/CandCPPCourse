//
// Created by jenia on 04/09/2016.
//

#include "Point.h"


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

std::string Point::toString()
{
}

