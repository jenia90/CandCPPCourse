#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Point.h"

struct Node
{
	/**
	 * @Brief Empty node constructor.
	 */
	Node(): _p(nullptr), next(nullptr)
	{
	}

	/**
	 * @brief Constructor that inits the _p and next fields.
	 * @param point Point pointer.
	 * @param next next Node pointer.
	 */
	Node(Point* point, Node* next)
		: _p(point),
		  next(next)
	{
	}
	
	/**
	 * @brief Getters for Node member fields.
	 */
	Node* getNext() { return next; }
	Point* getPoint() { return _p; }

	/**
	 * @brief Destructor. Frees allocated memory blocks of _p and next.
	 */
	~Node()
	{
		delete _p;
		delete next;
	}
private:
	Point* _p;
	Node* next;
}; 

class LinkedList
{
	int _size;
	Node *_head;
public:
	/**
	 * @brief Constructor.
	 */
	LinkedList();


	/**
	 * @brief Adds a new node to the head with the give Point as its data
	 * @param p Point pointer
	 * @return true if successful; false otherwise.
	 */
	bool addNode(Point* p);
	/**
	 * @brief Removes the head of the list and returns the Point object it held.
	 * @return Point object
	 */
	Point& removeHead();
	
	/**
	 * @brief Gets the size of the list
	 * @return int representing size of the list
	 */
	int size() { return _size; }
	
	/**
	 * @brief Destructor. Deletes all remaining nodes.
	 */
	~LinkedList();
};

#endif
