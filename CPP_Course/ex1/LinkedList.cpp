#include "LinkedList.h"

LinkedList::LinkedList(): _size(0), _head(new Node())
{
}

bool LinkedList::addNode(Point p)
{
	if(_head->getPoint() == p)
	{
		return false;
	}
	_head = new Node(p, _head);
	if (!_head) return false;
	_size++;
	return true;
}

Point& LinkedList::removeHead()
{
	Point point;
	if (_head)
	{
		Node next = *_head;
		point = _head->getPoint();
		_head = _head->getNext();
		_size--;
	}

	return point;
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
