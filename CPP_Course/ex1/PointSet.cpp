//
// Created by jenia on 04/09/2016.
//

#include <algorithm>
#include "PointSet.h"

PointSet::PointSet() : _size(0), _capacity(DEFAULT_CAPACITY), _pointSet(new Point[DEFAULT_CAPACITY])
{
}

PointSet::PointSet(int capacity) : _size(0), _capacity(capacity), _pointSet(new Point[capacity])
{
}

PointSet::~PointSet()
{
	delete[] _pointSet;
}

bool PointSet::add(const Point& p)
{
	if(_size == _capacity)
	{
		resizeSet(_capacity *= 2);
	}

	if (isInSet(p) == NOT_FOUND)
	{
		_pointSet[_size++] = p;
		return true;
	}

	return false;
}

void PointSet::resizeSet(int newCapacity)
{
	Point *newSet = new Point[newCapacity];

	std::copy_n(_pointSet, size(), newSet);

	delete[] _pointSet;

	_capacity = newCapacity;

	_pointSet = newSet;
}

int PointSet::isInSet(const Point& p)
{
	for (int i = 0; i < size(); i++)
	{
		if (_pointSet[i] == p)
		{
			return i;
		}
	}

	return NOT_FOUND;
}

bool PointSet::remove(Point p, int index = NOT_FOUND)
{
	if (index == NOT_FOUND)
	{
		if ((index = isInSet(p)) == NOT_FOUND)
		{
			return false;
		}
	}

	for (int i = index; i < (_size - 1); i++)
	{
		_pointSet[i] = _pointSet[i + 1];
	}

	_size--;
	return true;
}

PointSet& PointSet::sort(int begin, int end, int (*compare)(Point, Point))
{
	if(compare)
	{
		std::sort(_pointSet + begin, _pointSet + end, compare);
	}
	else
	{
		std::sort(_pointSet + begin, _pointSet + end);
	}

	return *this;
}

bool PointSet::removeLast()
{
	if(_size - 1 > 0)
	{
		_pointSet[_size--] = Point();
		return true;
	}

	return false;
}

int PointSet::size() const
{
	return _size;
}

std::string PointSet::toString()
{
	std::stringstream ss;

	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
		{
			ss << _pointSet[i].toString();
		}
	}
	else
	{
		ss << "" << std::endl;
	}

	return ss.str();
}

