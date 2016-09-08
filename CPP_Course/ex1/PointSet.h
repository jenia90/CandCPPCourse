/**
 * @file PointSet.h
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Header file containg the declarations of the PointSet class and its members
 * @section DESCRIPTION:
 * This class represents a set of points in 2D space.
 * More thorough explanation about the class is in the README file attached to the project.
 */

#include <iostream>
#ifndef POINTSET_H
#define POINTSET_H

#define NOT_FOUND -1
#define DEFAULT_CAPACITY 2
#define EXPANSION_COEFFICIENT 2
#define EMPTY ""

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

    /**
     * @brief Helper function for the equality and non-equality operator overloads.
     * It checks if the current set and the passed in set are equal (have the same points)
     * and returns true if yes; false otherwise.
     * @param pSet The other PointSet we want to compare
     * @return true if they are equal; false otherwise.
     */
    bool isEqual(PointSet pSet);

public:
    /**
     * @brief Empty constructor inits the set with default capacity
     */
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

    /**
     * @brief checks if this set and passed in set don't have the same points or size
     * @param pSet the set to compare to
     * @return true if the sets aren't equal; false otherwise
     */
	bool operator !=(const PointSet& pSet);

    /**
    * @brief checks if this set and passed in set have the same points or size
    * @param pSet the set to compare to
    * @return true if the sets are equal; false otherwise
    */
	bool operator ==(const PointSet& pSet);

    /**
     * @brief Subtraction operator overload, returns the set of points which are in this set but
     * not in the other set.
     * @param pSet the set of points which we will subtract
     * @return new PointSet object containing points which are in the first set but not in the
     * second
     */
	PointSet operator -(const PointSet& pSet);

    /**
     * @brief Intersection operator overload, returns the set of points which are in both sets
     * @param pSet the set of points which we will compare to
     * @return new PointSet object containing points which are in both sets.
     */
	PointSet operator &(const PointSet& pSet);

    /**
     * @brief Assignment operator overload, replaces the points in this set with the points from
     * the given set
     * @param pSet the set of points which will replace the current set
     * @return PointSet reference after updating the points.
     */
    PointSet& operator =(const PointSet& pSet);
};


#endif //POINTSET_H
