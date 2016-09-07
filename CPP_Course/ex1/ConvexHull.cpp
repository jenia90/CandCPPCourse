//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include <algorithm>


void printConvex(Point convex[], int size)
{
	std::cout << "result:" << std::endl;
	for (int i = 0; i < size; ++i)
	{
		std::cout << convex[i].toString();
	}
}

Point* grahamScan(PointSet& pSet, int *numOfPoints)
{
	int currIndex = 0;
	Point& p0 = pSet.getSet()[currIndex];
	Point stk[pSet.size()];

	stk[currIndex++] = p0;
	for(; currIndex < 3; currIndex++)
	{
		stk[currIndex] = pSet.getSet()[currIndex];
	}

	for (int i = currIndex; i < pSet.size() && currIndex < pSet.size(); i++)

		if (pSet.getSet()[currIndex].isInit())
		{

			if (stk[i - 1] < stk[i] && pSet.getSet()[currIndex] < stk[i])
			{
				stk[i++] = pSet.getSet()[currIndex++];
				continue;
			}
			else
			{
				stk[i] = pSet.getSet()[currIndex++];
			}

			*numOfPoints = i;
		}

	for (Point point : stk)
	{
		std::cout << "Points in stack:" << std::endl << point.toString();
	}
	return stk;
}

int main(int argc, char* argv[])
{
	std::string line;
	int numPoints;
	Point p, *convex;
	PointSet pSet = PointSet(2);


	while ((std::cin >> p).peek() != -666)
	{
		if(p.getX() == -666)
			break;

		pSet.add(p);
		
	}
	std::cout << "Created set" << std::endl; //TODO: Remove
	std::sort(pSet.getSet(), pSet.getSet()+pSet.size());
	std::cout << "Sorted" << std::endl; //TODO: Remove
	convex = grahamScan(pSet, &numPoints);
	printConvex(convex, numPoints);

	return 0;
}
