//
// Created by jenia on 04/09/2016.
//

#include "PointSet.h"

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
/*
void PointSet::sort(Point* pSet, int low, int high)
{
	int mid;
	if (low <= high)
	{
		mid = (low + high) / 2;
		sort(pSet, low, mid);
		sort(pSet, mid + 1, high);
		merge(pSet, low, mid, high);
	}
}

void PointSet::merge(Point* pSet, int low, int mid, int high)
{
	int n1 = mid - low + 1, n2 = high - mid;
	Point leftArr[n1], rightArr[n2];

	for (int i = 0; i < n1; ++i)
	{
		leftArr[i] = pSet[low + i];
	}
	for (int i = 0; i < n2; i++)
	{
		rightArr[i] = pSet[mid + 1 + i];
	}

	int i = 0, j = 0, k = 0;
	while (i < n1 && j < n2)
	{
		if (leftArr[i].compare(rightArr[j]))
		{
			pSet[k] = leftArr[i];
			i++;
		}
		else if (leftArr[i].compare(rightArr[j]) > 0)
		{
			pSet[k] = rightArr[j];
			j++;
		}
		else
		{
			pSet[k] = rightArr[i];
			i++;
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		pSet[k] = leftArr[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		pSet[k] = rightArr[j];
		j++;
		k++;
	}
	_size = k;
}*/

/*
void PointSet::swap(Point& p1, Point& p2)
{
	Point& temp = p1;
	p1 = p2;
	p2 = temp;
}*/

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
