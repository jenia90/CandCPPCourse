#include "LinkedList.h"

LinkedList::LinkedList(Point& p): _size(0), _head(new Node(p, nullptr))
{
}

bool LinkedList::addNode(Point& p)
{
	Node& newNode = new Node(p, _head);
}

bool LinkedList::removeNode(Point& p)
{
}

int LinkedList::size()
{
	return _size;
}

LinkedList::~LinkedList()
{
	do
	{
		Node next = _head.next;

	}
	while (_head != nullptr);
}
