//
// Created by jenia on 04/09/2016.
//

#ifndef POINTSET_H
#define POINTSET_H

#include <iostream>
#include "Point.h"

/**
 * @brief A class representing a mathematical set of points
 */
class PointSet
{
	/**
	* @brief an array to hold the set of points.
	*/
	Point *_pointSet;
	int _size;

public:
	/**
	 * Ctor
	 */
	PointSet();
	/**
	 * Destructor
	 */
	~PointSet();

	/**
	 * @brief Adds a new point to the set
	 * @param p Point to add
	 * @return true if add was successful; false otherwise.
	 */
	bool add(Point& p);

	/**
	 * @brief removes a point from the set
	 * @param p Point to remove
	 * @return true if removal was successful; false otherwise.
	 */
	bool remove(Point& p);

	/**
	 * @breif returns the size of the set
	 * @return size of the set
	 */
	int size();

	/**
	 * @brief Prints the set in specialized format.
	 */
	std::string toString();
};


#endif //POINTSET_H
