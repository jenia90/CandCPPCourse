//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include "LinkedList.h"

PointSet& createPointSet(LinkedList *list)
{
	PointSet point_set = PointSet(list->size());
}

int main(int argc, char* argv[])
{
	int x_i, y_i, delimIdx;
	std::string line;
	Point p;
	LinkedList list = LinkedList();

	while (std::cin >> p)
	{
		
		list.addNode(p);
	}

	PointSet pSet = createPointSet(list);

	return 0;
}
