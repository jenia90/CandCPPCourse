#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Point.h"

struct Node
{
	Node(): _p(), next()
	{
	}
	Node(Point& point, Node& next)
		: _p(point),
		  next(next)
	{
	}
	
	Node& getNext() const;
	Point& getPoint() const;


	~Node()
	{	
	}
private:
	Point& _p;
	Node& next;
}; 

class LinkedList
{
	Node& _head;
	int _size;
public:
	LinkedList();
	bool addNode(Point p);
	Point& removeHead();
	int size() const;
	~LinkedList();
};

#endif
