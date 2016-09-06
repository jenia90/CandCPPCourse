#include "LinkedList.h"

LinkedList::LinkedList(): _size(0), _head(new Node())
{
}

bool LinkedList::addNode(Point* p)
{
	Node *newNode = new Node(p, _head);
	_head = newNode;
	_size++;
	return true;
}

Point& LinkedList::removeHead()
{
	Point *point = nullptr;
	if (_head)
	{
		Node *next = _head;
		point = _head->getPoint();
		_head = _head->getNext();
		delete next;
		_size--;
	}

	return *point;
}

LinkedList::~LinkedList()
{
	Node *curr = _head;

	while (curr)
	{
		delete curr;
		_head = _head->getNext();
		curr = _head;
	}
}
