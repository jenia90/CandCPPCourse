//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include "LinkedList.h"

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
}

PointSet createPointSet(LinkedList list)
{
	PointSet pSet = PointSet(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		pSet.add(list.removeHead());
	}
	return pSet;
}

void printConvex(Point *convex, int size)
{
	std::cout << "result:" << std::endl;
	for (int i = 0; i < size; ++i)
	{
		std::cout << convex[i].toString();
	}
}

Point* grahamScan(PointSet pSet, int *numOfPoints)
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
	LinkedList list = LinkedList();

	while (std::cin >> p)
	{
		list.addNode(&p);
	}

	PointSet pSet = createPointSet(list);
	pSet.sort(pSet.getSet(), 0, pSet.size());
	printConvex(grahamScan(pSet, &numPoints), numPoints);

	return 0;
}
