//
// Created by jenia on 04/09/2016.
//

#include "Point.h"
#include <iostream>

Point::Point() : _x(0), _y(0), _isInit(false)
{
}

Point::Point(int x, int y): _x(x), _y(y), _isInit(true)
{
}

Point::~Point()
{
}

void Point::set(const int x, const int y)
{
	_x = x;
	_y = y;

	_isInit = true;
}

Point& Point::operator=(const Point& p)
{
	this->set(p.getX(), p.getY());
	return *this;
}

bool Point::operator==(const Point& p) const
{
	return (_x == p.getX()) && (_y == p.getY());
}

bool Point::operator !=(const Point& p) const
{
	return (_x != p.getX()) || (_y != p.getY());
}

Point& Point::operator -(const Point& p)
{
	this->set(_x - p.getX(), _y - p.getY());
	return *this;
}

bool Point::operator<(const Point &p) const
{
	if(_x != p.getX())
	{
		return _x < p.getX();
	}

	return _y < p.getY();
}

std::istream& operator>>(std::istream& is, Point& point)
{
	try
	{
		std::string str;
		is >> str;
		unsigned int delimIdx = str.find(DELMITER);
		point.set(std::stoi(str.substr(0, delimIdx)), std::stoi(str.substr(delimIdx + 1, str.size() - 1)));
		return is;
	}
	catch (...)
	{
		std::cerr << "Invalid input!";
		return is;
	}
}

std::string Point::toString()
{
	std::ostringstream oss;
	oss << _x << DELMITER << _y << std::endl;
	return oss.str();
}

