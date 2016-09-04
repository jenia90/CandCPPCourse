//
// Created by jenia90 on 9/4/16.
//

#include <iostream>
#include "Point.h"
#include "PointSet.h"
#include "LinkedList.h"

PointSet& createPointSet(LinkedList *list)
{
	PointSet point_set;
}

int main(int argc, char* argv[])
{
	int x_i, y_i, delimIdx;
	std::string line;
	LinkedList* list = new LinkedList();

	while (std::getline(std::cin, line))
	{
		delimIdx = line.find(",");
		x_i = std::stoi(line.substr(0, delimIdx));
		y_i = std::stoi(line.substr(delimIdx + 1, line.length() - 1));

		Point* p = new Point(x_i, y_i);
		list->addNode(p);
	}

	PointSet pSet = createPointSet(list);

	return 0;
}
