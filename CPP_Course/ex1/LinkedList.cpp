#include "LinkedList.h"

Node& Node::getNext() const
{
	return next;
}

Point& Node::getPoint() const
{
	return _p;
}

LinkedList::LinkedList(): _size(0), _head(Node())
{
}

bool LinkedList::addNode(Point p)
{
	Node newNode = Node(p, _head);
	_head = newNode;
	_size++;
	return true;
}

Point& LinkedList::removeHead()
{
	Point point;
	if (_head)
	{
		Node next = _head;
		point = _head.getPoint();
		_head = _head.getNext();
		delete next;
		_size--;
	}

	return point;
}

int LinkedList::size() const
{
	return _size;
}

LinkedList::~LinkedList()
{
	Node curr;

	while (_head != nullptr)
	{
		curr = _head;
		_head = _head.getNext();
		delete curr;
	}
}
