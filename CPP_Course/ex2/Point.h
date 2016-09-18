/**
 * @file Point.h
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Header file containg the declarations of the Point class and its members
 * @section DESCRIPTION:
 * This class represents a point in 2D space.
 */
#ifndef POINT_H
#define POINT_H

#include "Defs.h"
#include <string>

/**
 * @brief a class representing a point
 */
class Point
{
	const std::string name = "Point";

    CordType _x, _y;

    /**
     * @brief Helper method to check if 2 points are equal;
     * @param p the second Point object reference
     * @return true if equal; false otherwise.
     */
	bool isEqual(const Point& p) const;
public:
    /**
     * @brief Empty constructor, sets the coordinates to 0 and init state to fasle.
     */
	Point();
	/**
	 * @brief Ctor
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	Point(const CordType x, const CordType y);

	/**
	 * Destructor
	 */
	~Point();

    /**
     * @brief getter function for the X value
     * @return X value of the point
     */
    CordType getX() const
	{
		return _x;
	}

    /**
     * @brief getter function for the Y value
     * @return Y value of the point
     */
    CordType getY() const
	{
		return _y;
	}

    /**
     * @brief assignment operator overload, assigns the coordinates of the passed in point to
     * this point.
     * @param p Point which corrdinates we will assign
     * @return updated point
     */
	Point& operator=(const Point& p);

    /**
     * @brief equality operator overload to check if this point is equal to the other point
     * @param p Point to compare
     * @return true if coordinates are equal; false otherwise
     */
	bool operator ==(const Point& p) const;

    /**
     * @brief non-equality operator overload
     * @param p point to compare
     * @return true if points are not equal; false otherwise
     */
	bool operator !=(const Point& p) const;
};


#endif //POINT_H
