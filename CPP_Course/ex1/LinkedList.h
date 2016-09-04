#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Point.h"

struct Node
{
	Node(Point& point, Node& next)
		: _p(point),
		  next(next)
	{
	}

	Point _p;
	Node& next;

	~Node()
	{
		delete _p;

	}
};

class LinkedList
{
	Node& _head;
	int _size;
public:
	LinkedList(Point& p);
	bool addNode(Point& p);
	bool removeNode(Point& p);
	int size();
	~LinkedList();
};

#endif
