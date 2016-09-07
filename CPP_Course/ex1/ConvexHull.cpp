//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

Point p0;

/**
 * @brief Prints all the points which create the convex hull.
 * @param convex array of Point objects
 * @param size number of points in the array.
 */
void printConvex(PointSet& convex, int size)
{
	std::cout << "result:" << std::endl;
	for (int i = 0; i < size; ++i)
	{
		std::cout << convex.toString();
	}
}

void swap(Point &p1, Point &p2) noexcept
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2)
{
	return (p1.getX() - p2.getX())*(p1.getX() - p2.getX()) +
		(p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}

int orientation(Point p, Point q, Point r)
{
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
		(q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0;  // colinear
	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int compare(const void* vp1, const void* vp2)
{
	Point *p1 = (Point *)vp1;
	Point *p2 = (Point *)vp2;

	if (p1->isInit() && p2->isInit())
	{
		// Find orientation
		int o = orientation(p0, *p1, *p2);
		if (o == 0)
			return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;

		return (o == 2) ? -1 : 1;
	}
	return -1;
}

/**
 * @brief Implementation of graham scan algorithm to find the convex hull in a set of points.
 * @param pSet PointSet object reference containing all the points.
 * @param numOfPoints pointer to number of points integer which will be updated with the number
 * of points in the convex hull.
 * @return array of Point objects making the convex hull of the PointSet.
 */
PointSet& grahamScan(PointSet& pSet, int *numOfPoints)
{
	PointSet cHull = PointSet(pSet.size());
	int currIndex = 0;
	Point& p0 = pSet.getSet()[currIndex++];
	cHull.add(p0);
	cHull.add(pSet.getSet()[currIndex++]);
	*numOfPoints = currIndex;

	for(int i = currIndex; i < pSet.size(); i++)
	{
		Point p = pSet.getSet()[i];
		*numOfPoints++;
		while(orientation(cHull.getSet()[cHull.size() - 2], cHull.getSet()[cHull.size() - 1], p) != 2)
		{
			cHull.removeLast();
			*numOfPoints--;
		}

		cHull.add(p);
	}
	return cHull;
}

// TODO: REMOVE
PointSet myRun()
{
	PointSet pointSet = PointSet(2);
	int lim = 50;
	for (int i = -1 * lim; i <= lim; i++)
	{
		for (int j = -1 * lim; j <= lim; j++)
		{
			pointSet.add(Point(i, j));
		}
	}
	pointSet.add(Point(0, lim + 1));
	pointSet.add(Point(0, (-1 * lim) - 1));
	pointSet.add(Point(lim + 1, 0));
	pointSet.add(Point((-1 * lim) - 1, 0));
	return pointSet;
}

int main()
{
	int numPoints;
	Point p;
	PointSet convex, pSet = myRun();

	/*
	while (std::cin >> p)
	{
		pSet.add(p);
	}*/

	// sort the set of points according to their polar angle.
	int minY = pSet.getSet()[0].getY(), min = 0;
	for (int i = 1; i < pSet.size(); i++)
	{
		int y = pSet.getSet()[i].getY();

		// Pick the bottom-most or chose the left
		// most point in case of tie
		if ((y < minY) || (minY == y && pSet.getSet()[i].getX() < pSet.getSet()[min].getX()))
		{
			minY = pSet.getSet()[i].getY(), min = i;
		}
	}

	swap(pSet.getSet()[0], pSet.getSet()[min]);

	p0 = pSet.getSet()[0];

	std::qsort(&pSet.getSet()[1], pSet.size() - 1, sizeof(Point), compare);

	int m = 1; // Initialize size of modified array
	for (int i = 1; i < pSet.size(); i++)
	{
		// Keep removing i while angle of i and i+1 is same
		// with respect to p0
		while (i < pSet.size() - 1 && orientation(p0, pSet.getSet()[i],
			pSet.getSet()[i + 1]) == 0)
			i++;


		pSet.getSet()[m] = pSet.getSet()[i];
		m++;  // Update size of modified array
	}

    std::cout << "num of points in set: " << pSet.size() << std::endl;
	// get the convex hull set of points.
	convex = grahamScan(pSet, &numPoints);

    std::cout << "num of points in convex: " << numPoints << std::endl;
	// print points in the convex hull.
	printConvex(convex, numPoints);

	return 0;
}

