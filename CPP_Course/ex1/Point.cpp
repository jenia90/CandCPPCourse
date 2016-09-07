//
// Created by jenia on 04/09/2016.
//

#include "Point.h"
#include <iostream>

Point::Point() : _x(0), _y(0), isInit(false)
{
}

Point::Point(int x, int y): _x(x), _y(y), isInit(true)
{
}

Point::~Point()
{
}

void Point::set(int x, int y)
{
	_x = x;
	_y = y;

	isInit = true;
}

Point& Point::operator=(const Point& p)
{
	this->set(p.getX(), p.getY());
}

int Point::compare(const Point& p)
{
	int yComp = this->getY() - p.getY();

	if (!yComp)
	{
		return this->getX() - p.getX();
	}

	return yComp;
}

int Point::compare(const Point& p1, const Point& p2)
{
	int yComp = p1.getY() - p2.getY();

	if (!yComp)
	{
		return p1.getX() - p2.getX();
	}

	return yComp;
}

bool Point::operator==(const Point& p) const
{
	return (this->_x == p._x) && (this->_y == p._y);
}

int operator^(Point p1, Point p2)
{
	return p1.getX() * p2.getY() - p1.getY() * p2.getX();;
}

bool Point::operator<(Point p)
{
	if (this->getY() == 0 && this->getX() > 0)
	{
		return true; //angle of p1 is 0, thus p2>p1
	}
	if (p.getY() == 0 && p.getX() > 0)
	{
		return false; //angle of p2 is 0 , thus p1>p2
	}
	if (this->getY() > 0 && p.getY() < 0)
	{
		return true; //p1 is between 0 and 180, p2 between 180 and 360
	}
	if (this->getY() < 0 && p.getY() > 0)
	{
		return false;
	}

	return (*this^p) > 0; //return true if p1 is clockwise from p2
}

std::istream& operator>>(std::istream& is, Point& point)
{
	try
	{
		std::string str;
	is >> str;
	int delimIdx = str.find(",");
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
	oss << _x << "," << _y << std::endl;
	return oss.str();
}

