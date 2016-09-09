/**
 * @file PointSet.cpp
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Code file containg the declarations of the PointSet class and its members
 * @section DESCRIPTION:
 * This class represents a set of points in 2D space.
 * More thorough explanation about the class is in the README file attached to the project.
 */

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
		resizeSet(_capacity *= EXPANSION_COEFFICIENT);
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
	Point *newSet = new Point[_capacity = newCapacity];
	std::copy_n(_pointSet, _size, newSet);
	delete[](_pointSet);
	_pointSet = newSet;
}

int PointSet::isInSet(const Point& p) const
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
		_size--;
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

		return ss.str();
	}
	ss << std::endl;
	return ss.str();

}

bool PointSet::isEqual(PointSet pSet)
{
    if(this->size() != pSet.size())
    {
        return false;
    }

    for (int i = 0; i < this->_size; ++i)
    {
        if(pSet.isInSet(this->_pointSet[i]) != NOT_FOUND)
        {
            return false;
        }
    }

    return true;
}

bool PointSet::operator!=(const PointSet& pSet)
{
    return !isEqual(pSet);
}

bool PointSet::operator==(const PointSet& pSet)
{
    return isEqual(pSet);
}

PointSet PointSet::operator-(const PointSet& pSet)
{
    PointSet newSet;
    for (int i = 0; i < this->size(); ++i)
    {
		Point p = this->_pointSet[i];
        if(pSet.isInSet(p) == NOT_FOUND)
        {
            newSet.add(p);
        }
    }

    return newSet;
}

PointSet PointSet::operator&(const PointSet& pSet)
{
    PointSet newSet;
    int size = this->_size <= pSet.size() ? this->_size : pSet.size();
    for (int i = 0; i < size; ++i)
    {
		Point p = this->_pointSet[i];
        if(pSet.isInSet(p) != NOT_FOUND)
        {
            newSet.add(p);
        }
    }

    return newSet;
}

PointSet& PointSet::operator=(const PointSet& pSet)
{
    // check if its not self assignment
    if (this != &pSet) 
    {
        // check if current set and new set are of different size, if yes, create a new set of
        // given capacity
        if (this->size() != pSet.size())
        {
            delete[] _pointSet; // delete old set
            _pointSet = new Point[pSet._capacity]; // create new set with given capacity
            this->_size = 0; // reset size field
            this->_capacity = pSet._capacity; // set capacity field
        }

        // add every Point to the new set
        for(int i = 0; i < pSet.size(); i++)
        {
            this->add(pSet.getSet()[i]);
        }
    }
    return *this;
}

