//
// Created by jenia on 04/09/2016.
//

#include "PointSet.h"
#include <algorithm>

PointSet::PointSet(int capacity) : _size(0), _capacity(capacity), _pointSet(new Point[capacity])
{
}

PointSet::~PointSet()
{
	delete[] _pointSet;
}

bool PointSet::add(Point& p)
{
	if(_size == _capacity)
	{
		_pointSet = resizeSet(_capacity *= 2);
	}

	if (isInSet(p) == NOT_FOUND)
	{
		_pointSet[_size++] = p;
		return true;
	}

	return false;
}

Point* PointSet::resizeSet(int newCapacity)
{
	Point *newSet = new Point[newCapacity];
	std::copy_n(_pointSet, size(), newSet);
	delete[] _pointSet;
	_capacity = newCapacity;
	return newSet;
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

inline bool PointSet::remove(Point p, int index = NOT_FOUND)
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

int PointSet::size() const
{
	return _size;
}

std::string PointSet::toString()
{
	std::ostringstream oss;

	if (_size > 0)
	{
		for (int i = 0; i < _size; i++)
		{
			oss << _pointSet[i].toString();
		}
	}
	else
	{
		oss << "" << std::endl;
	}

	return oss.str();
}
