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

/**
 * @brief Empty constructor, sets the coordinates to 0 and init state to fasle.
 */
Point::Point() : _x(0), _y(0)
{
}

/**
 * @brief Ctor
 * @param x the x coordinate
 * @param y the y coordinate
 */
Point::Point(CordType x, CordType y): _x(x), _y(y)
{
}

/**
 * Destructor
 */
Point::~Point()
{
}

/**
 * @brief assignment operator overload, assigns the coordinates of the passed in point to
 * this point.
 * @param p Point which corrdinates we will assign
 * @return updated point
 */
Point& Point::operator=(const Point& p)
{
	// check if its not self assignment
	if (this != &p)
	{
		_x = p._x;
		_y = p._y;
	}
	return *this;
}

/**
 * @brief Helper method to check if 2 points are equal;
 * @param p the second Point object reference
 * @return true if equal; false otherwise.
 */
bool Point::isEqual(const Point &p) const
{
	return (_x == p.getX()) && (_y == p.getY());
}

/**
 * @brief equality operator overload to check if this point is equal to the other point
 * @param p Point to compare
 * @return true if coordinates are equal; false otherwise
 */
bool Point::operator==(const Point& p) const
{
	return isEqual(p);
}

/**
 * @brief non-equality operator overload
 * @param p point to compare
 * @return true if points are not equal; false otherwise
 */
bool Point::operator !=(const Point& p) const
{
	return !isEqual(p);
}

