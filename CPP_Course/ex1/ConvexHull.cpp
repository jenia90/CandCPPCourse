//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include "LinkedList.h"

PointSet createPointSet(LinkedList list)
{
	PointSet pSet = PointSet(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		pSet.add(list.removeHead());
	}
	return pSet;
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

	return 0;
}
