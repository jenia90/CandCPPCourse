//
// Created by jenia on 04/09/2016.
//

#ifndef POINTSET_H
#define POINTSET_H

#define NOT_FOUND -1

#include "Point.h"

/**
 * @brief A class representing a mathematical set of points
 */
class PointSet
{
	int _size, _capacity;
	Point *_pointSet;

public:
	/**
	 * Ctor
	 */
	PointSet(int capacity);
	/**
	 * Destructor
	 */
	~PointSet();

	inline Point *getSet() { return _pointSet; }

	/**
	 * @brief Adds a new point to the set
	 * @param p Point to add
	 * @return true if add was successful; false otherwise.
	 */
	bool add(Point& p);
	Point *resizeSet(int newCapacity);

	int isInSet(const Point& p);

	/**
	 * @brief removes a point from the set
	 * @param p Point to remove
	 * @return true if removal was successful; false otherwise.
	 */
	bool remove(Point p, int index);

	/**
	 * @breif returns the capacity of the set
	 * @return capacity of the set
	 */
	int size() const;

	/**
	 * @brief Prints the set in specialized format.
	 */
	std::string toString();

	bool operator !=(const PointSet& pSet);
	bool operator ==(const PointSet& pSet);
	PointSet operator -(const PointSet& pSet);
	PointSet operator &(const PointSet& pSet);
};


#endif //POINTSET_H
