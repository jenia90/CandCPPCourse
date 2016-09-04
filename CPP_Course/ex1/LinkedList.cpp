#include "LinkedList.h"

Node* Node::getNext()
{
	return this->next;
}

Point* Node::getPoint()
{
	return this->_p;
}

LinkedList::LinkedList(): _size(0), _head(nullptr)
{
}

bool LinkedList::addNode(Point* p)
{
	Node *newNode = new Node(p, _head);
	if (newNode)
	{
		_head = newNode;
		_size++;
		return true;
	}

	return false;
}

Point* LinkedList::removeHead()
{
	Point *point;
	if (_head)
	{
		Node *next = _head;
		point = _head->getPoint();
		_head = _head->getNext();
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
	Node *curr;

	while (_head != nullptr)
	{
		curr = _head;
		_head = _head->getNext();
		delete curr;
	}
}
