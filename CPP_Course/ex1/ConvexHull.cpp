//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

#define COLLINEAR 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2
#define TOP 1
#define NEXT_TO_TOP 2
Point p0;

/**
 * @brief Prints all the points which create the convex hull.
 * @param convex array of Point objects
 * @param size number of points in the array.
 */
void printConvex(PointSet convex)
{
	std::cout << "result:" << std::endl << convex.toString();
}

/**
 * @brief Swaps to points
 * @param p1 Point 1
 * @param p2 Point 2
 */
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

/**
 * @brief Calculates the distance squared of 2 Points
 * @param p1 Point 1
 * @param p2 Point 2
 * @return product of multiplication
 */
int distanceSquared(Point p1, Point p2)
{
	return (p1.getX() - p2.getX())*(p1.getX() - p2.getX()) +
		(p1.getY() - p2.getY())*(p1.getY() - p2.getY());
}

/**
 * @brief Calculates the orientation of 2 points in respect to the third one
 * @param p Point 1
 * @param q Point 2
 * @param r Point 3
 * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
 */
int orientation(Point a, Point b, Point c)
{
	int val = (b.getX() - a.getX()) * (c.getY() - a.getY()) -
              (b.getY() - a.getY()) * (c.getX() - a.getX());

    return val > 0 ? COUNTERCLOCKWISE : val < 0 ? CLOCKWISE : COLLINEAR;
}

/**
 * @brief Helper function used to pass as a function pointer to the qsort function for comparing
 * 2 Points.
 * @param vp1 void pointer to Point 1
 * @param vp2 void pointer to Point 2
 * @return
 */
int compare(Point a, Point b)
{
    const int order = orientation(p0, a, b);

    if (order == COLLINEAR)
    {
        return distanceSquared(p0, a) < distanceSquared(p0, b);
    }

    return (order == COUNTERCLOCKWISE);
}

/**
 * @brief Implementation of graham scan algorithm to find the convex hull in a set of points.
 * @param pSet PointSet object reference containing all the points.
 * @param numOfPoints pointer to number of points integer which will be updated with the number
 * of points in the convex hull.
 * @return array of Point objects making the convex hull of the PointSet.
 */
PointSet grahamScan(PointSet& pSet)
{
	PointSet cHull;
	cHull.add(p0);
	cHull.add(pSet.getSet()[TOP]);
    cHull.add(pSet.getSet()[NEXT_TO_TOP]);

	for(int i = 3; i < pSet.size(); i++)
	{
        Point p = pSet.getSet()[i];
		while(orientation(cHull.getSet()[cHull.size() - NEXT_TO_TOP], cHull.getSet()[cHull.size() - TOP], p)
              != COUNTERCLOCKWISE)
		{
			cHull.removeLast();
		}

		cHull.add(p);
	}
	return cHull;
}

// TODO: REMOVE
PointSet myRun()
{
	PointSet pointSet;
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
			minY = pSet.getSet()[i].getY();
            min = i;
		}
	}

	swap(pSet.getSet()[0], pSet.getSet()[min]);

	p0 = pSet.getSet()[0];
    pSet.sort(0, pSet.size() - 1, compare);

	int m = 1; // Initialize size of modified array
	for (int i = 1; i < pSet.size(); i++)
	{
		// Keep removing i while angle of i and i+1 is same
		// with respect to p0
		while (i < (pSet.size() - 1) && orientation(p0, pSet.getSet()[i], pSet.getSet()[i + 1]) == 0)
        {
            i++;
        }


		pSet.getSet()[m] = pSet.getSet()[i];
		m++;  // Update size of modified array
	}

	// get the convex hull set of points.
	convex = grahamScan(pSet);
	// print points in the convex hull.
	printConvex(convex);

	return 0;
}

