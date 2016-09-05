//
// Created by jenia on 04/09/2016.
//

#include "PointSet.h"

PointSet::PointSet(int size) : _size(0), _pointSet(new Point[size])
{
}

PointSet::~PointSet()
{
	delete[] _pointSet;
}

bool PointSet::add(Point& p)
{
	
	_pointSet[_size++] = p;
}

bool PointSet::remove(Point& p)
{
}

int PointSet::size()
{
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
