//
// Created by jenia on 04/09/2016.
//

#ifndef POINTSET_H
#define POINTSET_H

#define NOT_FOUND -1
#define DEFAULT_CAPACITY 2

#include "Point.h"
#include <algorithm>
#include <iostream>

/**
 * @brief A class representing a mathematical set of points
 */
class PointSet
{
	int _size, _capacity;
	Point *_pointSet;

	/**
	 * @brief Expands the array by creating a new array and moving all Points to it
	 * @param newCapacity size of the new array
	 */
    Point * resizeSet(int newCapacity);

    bool isEqual(PointSet pSet2);

public:
	PointSet();
	/**
	 * Ctor
	 */
	PointSet(int capacity);
	/**
	 * Destructor
	 */
	~PointSet();

	/**
	 * @brief getter for the set
	 * @return set of points.
	 */
    Point * getSet()const
    { return _pointSet; }

	/**
	 * @brief Adds a new point to the set
	 * @param p Point to add
	 * @return true if add was successful; false otherwise.
	 */
	bool add(const Point& p);

	/**
	 * @brief checks if a given point is in the set and returns its index if yes.
	 * @param p Point reference to find.
	 * @return index of the Point in the set; -1 otherwise.
	 */
	int isInSet(const Point& p)const;

	/**
	 * @brief removes a point from the set
	 * @param p Point to remove
	 * @return true if removal was successful; false otherwise.
	 */
	bool remove(Point p, int index);

	/**
	 * @brief removes the last point in the set.
	 * @return true if successful; false otherwise.
	 */
	bool removeLast();

    /**
     * @brief Sorts the set from begin index to end index using a given comparison function. If
     * no function was given it will use the std one.
     * @param begin begin index in the array
     * @param end end index in the array
     * @param compare comparison function pointer
     * @return sorted PointSet.
     */
	PointSet& sort(int begin, int end, int (*compare)(Point, Point) = nullptr);

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
    PointSet & operator =(const PointSet& pSet);
};


#endif //POINTSET_H
