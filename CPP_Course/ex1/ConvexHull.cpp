//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

/**
 * @brief Prints all the points which create the convex hull.
 * @param convex array of Point objects
 * @param size number of points in the array.
 */
void printConvex(Point *convex, int size)
{
	std::cout << "result:" << std::endl;
	for (int i = 0; i < size; ++i)
	{
		std::cout << convex[i].toString();
	}
}


/**
 * @brief Implementation of graham scan algorithm to find the convex hull in a set of points.
 * @param pSet PointSet object reference containing all the points.
 * @param numOfPoints pointer to number of points integer which will be updated with the number
 * of points in the convex hull.
 * @return array of Point objects making the convex hull of the PointSet.
 */
Point* grahamScan(PointSet& pSet, int *numOfPoints)
{
	int currIndex = 0;
	Point& p0 = pSet.getSet()[currIndex];
	Point *stk = new Point[pSet.size()];

	stk[currIndex++] = p0; // puts the the pivot point in the stack.

	// add 2 more points to the stack
	for(; currIndex < 3; currIndex++)
	{
		stk[currIndex] = pSet.getSet()[currIndex];
	}

	// for the rest of the points if the top and the next to the top point in the stack make a
	// right turn with the next point. If yes, we replace the top of the stack with the next 
	// point in the set. Otherwise, push the next point into our stack.
	for (int i = currIndex; i < pSet.size() && currIndex < pSet.size(); i++)

		if (pSet.getSet()[currIndex].isInit())
		{

			if (stk[i - 1] < stk[i] && pSet.getSet()[currIndex] < stk[i])
			{
				stk[i++] = pSet.getSet()[currIndex++];
			}
			else
			{
				stk[i] = pSet.getSet()[currIndex++];
			}

			*numOfPoints = i;
		}

	return stk;
}
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

int main(int argc, char* argv[])
{
	std::string line;
	int numPoints;
	Point p, *convex;
	PointSet pSet = myRun();

	/*
	while (std::cin >> p)
	{
		pSet.add(p);
	}*/

	// sort the set of points according to their polar angle.
	std::sort(pSet.getSet(), pSet.getSet() + pSet.size());

	// get the convex hull set of points.
	convex = grahamScan(pSet, &numPoints);

	// print points in the convex hull.
	printConvex(convex, numPoints);

	return 0;
}

