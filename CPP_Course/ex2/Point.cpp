/**
 * @file Point.cpp
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Code file containing the definitions of the Point class and its members
 * @section DESCRIPTION:
 * This class represents a point in 2D space.
 */

#include "Point.h"

Point::Point() : _x(0), _y(0), _isInit(false)
{
}

Point::Point(CordType x, CordType y): _x(x), _y(y), _isInit(true)
{
}

Point::~Point()
{
}

void Point::set(const CordType x, const CordType y)
{
	_x = x;
	_y = y;

	_isInit = true;
}

Point& Point::operator=(const Point& p)
{
	// check if its not self assignment
	if (this != &p)
	{
		_x = p._x;
		_y = p._y;
		_isInit = p._isInit;
	}
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
	if(isInit())
	{
		_x -= p.getX();
		_y -= p.getY();
		return *this;
	}
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
	}
	catch (...)
	{
		std::cerr << INVALID_INPUT << std::endl;
	}

	return is;
}

std::string Point::toString()
{
	std::ostringstream oss;
	oss << _x << DELMITER << _y << std::endl;
	return oss.str();
}

