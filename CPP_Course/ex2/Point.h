/**
 * @file Point.h
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Header file containg the declarations of the Point class and its members
 * @section DESCRIPTION:
 * This class represents a point in 2D space.
 * More thorough explanation about the class is in the README file attached to the project.
 */
#ifndef POINT_H
#define POINT_H

#define DELMITER ","
#define INVALID_INPUT "Invalid input!"

#include <sstream>
#include <iostream>

/**
 * @brief a class representing a point
 */
class Point
{
	double _x, _y;
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
	Point(double x, double y);

	/**
	 * Destructor
	 */
	~Point();

	/**
	 * @brief Sets the (x,y) coordinates of the point
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void set(const double x, const double y);

    /**
     * @brief getter function for the X value
     * @return X value of the point
     */
	double getX() const
	{
		return _x;
	}

    /**
     * @brief getter function for the Y value
     * @return Y value of the point
     */
	double getY() const
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

    /**
     * @brief Subtraction operator overload, returns the updated object after subtracting X and Y
     * value of the given point.
     * @param p Point object
     * @return Updated object reference
     */
	Point& operator -(const Point& p);

    /**
     * @brief Comparison operator overload, compares this point to the given point
     * @param p Point to compare
     * @return true if this point is smaller (On Y and X); false otherwise
     */
	bool operator<(const Point& p) const;

    /**
     * @brief input stream operator overload user for parsing the input from the user and
     * assigning the received value to the point object.
     * @param is Input stream
     * @param point Point reference which will be updated with the parsed values.
     * @return Input stream object.
     */
	friend std::istream& operator>>(std::istream& is, Point& point);

	/**
	 * @brief Prints the point in a specialized format
	 */
	std::string toString();
};


#endif //POINT_H
