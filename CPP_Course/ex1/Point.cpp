//
// Created by jenia on 04/09/2016.
//

#include "Point.h"

Point::Point() : _x(0), _y(0)
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

bool Point::operator==(const Point& p) const
{
	return (this->_x == p._x) && (this->_y == p._y);
}

std::istream& operator>>(std::istream& is, Point& point)
{
	std::string str;
	is >> str;
	int delimIdx = str.find(",");
	point.set(std::stoi(str.substr(0, delimIdx)), std::stoi(str.substr(delimIdx + 1, str.size() - 1)));
	return is;
}

std::string Point::toString()
{
	std::ostringstream oss;
	oss << _x << "," << _y << std::endl;
	return oss.str();
}

