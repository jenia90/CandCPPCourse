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

int operator^(Point p1, Point p2)
{
	return p1.getX() * p2.getY() - p1.getY() * p2.getX();;
}

bool operator<(Point p1, Point p2)
{
	if (p1.getY() == 0 && p1.getX() > 0)
	{
		return true; //angle of p1 is 0, thus p2>p1
	}
	if (p2.getY() == 0 && p2.getX() > 0)
	{
		return false; //angle of p2 is 0 , thus p1>p2
	}
	if (p1.getY() > 0 && p2.getY() < 0)
	{
		return true; //p1 is between 0 and 180, p2 between 180 and 360
	}
	if (p1.getY() < 0 && p2.getY() > 0)
	{
		return false;
	}

	return (p1^p2) > 0; //return true if p1 is clockwise from p2
}

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
}

void PointSet::swap(Point& p1, Point& p2)
{
	Point& temp = p1;
	p1 = p2;
	p2 = temp;
}

int PointSet::size()
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
