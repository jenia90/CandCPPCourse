//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include <algorithm>

/*
int operator^(Point p1, Point p2)
{
	return p1.getX() * p2.getY() - p1.getY() * p2.getX();;
}

bool operator<(Point p1, Point p2)
{
	if (p1.getY() == 0 && p1.getX() > 0)
	{
		return true; //angle of p1 is 0, thus p2>p1
	}
	if (p2.getY() == 0 && p2.getX() > 0)
	{
		return false; //angle of p2 is 0 , thus p1>p2
	}
	if (p1.getY() > 0 && p2.getY() < 0)
	{
		return true; //p1 is between 0 and 180, p2 between 180 and 360
	}
	if (p1.getY() < 0 && p2.getY() > 0)
	{
		return false;
	}

	return (p1^p2) > 0; //return true if p1 is clockwise from p2
}*/

void printConvex(Point *convex, int size)
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
	Point stack[pSet.size()];

	stack[currIndex++] = p0;
	for(; currIndex < 3; currIndex++)
	{
		stack[currIndex] = pSet.getSet()[currIndex];
	}

	for (int i = currIndex; i < pSet.size(); i++)
	{
		if(stack[i - 1] < stack[i] && pSet.getSet()[currIndex] < stack[i])
		{
			stack[i++] = pSet.getSet()[currIndex++];
			continue;
		}
		else
		{
			stack[i] = pSet.getSet()[currIndex++];
		}

		*numOfPoints = i;
	}


	return stack;
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
	std::cout << "Created set" << std::endl;
	std::sort(pSet.getSet(), pSet.getSet()+pSet.size());
	std::cout << "Sorted" << std::endl;
	Point *scanned = grahamScan(pSet, &numPoints);
	printConvex(scanned, numPoints);

	return 0;
}
