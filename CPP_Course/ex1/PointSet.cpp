//
// Created by jenia on 04/09/2016.
//

#include "PointSet.h"

PointSet::PointSet(): _size(0)
{
}

PointSet::~PointSet()
{
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
