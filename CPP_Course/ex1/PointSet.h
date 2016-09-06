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
	int _size;
	Point *_pointSet;

public:
	/**
	 * Ctor
	 */
	PointSet(int size);
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

	int isInSet(const Point p);

	/**
	 * @brief removes a point from the set
	 * @param p Point to remove
	 * @return true if removal was successful; false otherwise.
	 */
	bool remove(Point p, int index);

	/**
	 * @brief Methods sort and merge are the implementation of merge-sort sorting algorithm
	 * to sort the points in our set. Also, while sorting it skips duplicate points;
	 */
	void sort(Point* pSet, int low, int high);
	void merge(Point* pSet, int low, int mid, int high);

	void swap(Point& p1, Point&p2);

	/**
	 * @breif returns the size of the set
	 * @return size of the set
	 */
	int size();

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
