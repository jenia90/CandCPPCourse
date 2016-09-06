//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include "LinkedList.h"

bool operator<(Point p1, Point p2);

PointSet createPointSet(LinkedList list)
{
	PointSet pSet = PointSet(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		pSet.add(list.removeHead());
	}
	return pSet;
}

void grahamScan(PointSet pSet)
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
			currIndex++;
		}
	}

	//TODO: CONTINUE IMPLEMENTATION

}

int main(int argc, char* argv[])
{
	std::string line;
	Point p;
	LinkedList list = LinkedList();

	while (std::cin >> p)
	{
		
		list.addNode(&p);
	}

	PointSet pSet = createPointSet(list);
	pSet.sort(pSet.getSet(), 0, pSet.size());
	grahamScan(pSet);

	return 0;
}
