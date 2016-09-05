//
// Created by jenia on 04/09/2016.
//

#include "PointSet.h"

PointSet::PointSet(int capacity) : _size(0), _pointSet(new Point[capacity])
{
}

PointSet::~PointSet()
{
	delete[] _pointSet;
}

bool PointSet::add(Point& p)
{
	if (isInSet(p) == NOT_FOUND)
	{
		_pointSet[_size++] = p;
		return true;
	}

	return false;
}

int PointSet::isInSet(const Point p)
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

bool PointSet::remove(Point& p)
{
	int index;
	if((index = isInSet(p)) != NOT_FOUND)
	{
		for(int i = index; i < (_size - 1); i++)
		{
			_pointSet[i] = _pointSet[i + 1];
		}

		_size--;
		return true;
	}
	return false;
}

int PointSet::size()
{
	return _size;
}

bool PointSet::operator!=(const PointSet& pSet)
{
}

bool PointSet::operator==(const PointSet& pSet)
{
}

PointSet PointSet::operator-(const PointSet& pSet)
{
}

PointSet PointSet::operator&(const PointSet& pSet)
{
}
