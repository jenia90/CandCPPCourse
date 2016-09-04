//
// Created by jenia on 04/09/2016.
//

#ifndef POINT_H
#define POINT_H

#include <iostream>

/**
 * @brief a class representing a point
 */
class Point
{
	int _x, _y;
public:
	Point();
	/**
	 * @brief Ctor
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	Point(int x, int y);

	/**
	 * Destructor
	 */
	~Point();

	/**
	 * @brief Sets the (x,y) coordinates of the point
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void set(int x, int y);

	bool operator ==(const Point& p) const;

	/**
	 * @brief Prints the point in a specialized format
	 */
	std::string toString();
};


#endif //POINT_H
