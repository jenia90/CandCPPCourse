

#include <cmath>
#include <iostream>
#include "Line.h"

/**
 * Ctor
 * @param a 1st Point object ref
 * @param b 2nd Point object ref
 */
Line::Line(Point &a, Point &b)
{
    _points[FST_POINT] = a;
    _points[SEC_POINT] = b;
}

/**
 * dtor
 */
Line::~Line()
{
}

/**
 * @brief Calculates the length of this line
 * @return length of the line in 2D space
 */
CordType Line::getLength() const
{
    CordType len = sqrt(SQUARE(_points[SEC_POINT].getX() - _points[FST_POINT].getX()) +
                        SQUARE(_points[SEC_POINT].getY() - _points[FST_POINT].getY()));

    return len;
}

/**
 * @brief Calculates the slope of the line
 * @return slope of the line
 */
CordType Line::getSlope() const
{
    return fabs((_points[SEC_POINT].getY() - _points[FST_POINT].getY()) /
                (_points[SEC_POINT].getX() - _points[FST_POINT].getX()));
}

/**
 * @brief Checks if 2 lines are parallel to each other (slope diff is in given margin)
 * @param l Line object ref
 * @return true if parallel; false otherwise
 */
bool Line::operator||(const Line &l)
{
    return fabs(this->getSlope() - l.getSlope()) < EPSILON;
}

/**
 * Assignment operator.
 * @param l Line object reference
 * @return updated object reference
 */
Line &Line::operator=(const Line &l)
{
    if(this != &l)
    {
        for (int i = 0; i < 2; ++i)
        {
            _points[i] = l._points[i];
        }
    }

    return *this;
}

/**
 * @brief Helper method that checks if 2 lines are equal
 * @param l Line object ref
 * @return true if equal; false otherwise
 */
bool Line::isEqual(const Line& l)
{
    return (_points[FST_POINT] == l._points[FST_POINT]) &&
           (_points[SEC_POINT] == l._points[SEC_POINT]);
}

/**
 * @brief is equal operator. Checks if 2 lines are equal
 * @param l Line object reference
 * @return true if equal; false otherwise
 */
bool Line::operator==(const Line& l)
{
    return isEqual(l);
}

/**
 * @brief is not equal operator. Checks if 2 lines are not equal
 * @param l Line object reference
 * @return true if not equal; false otherwise
 */
bool Line::operator !=(const Line& l)
{
    return !isEqual(l);
}

/**
 * @brief Intersection operator
 * @param l Line object reference
 * @return true if 2 lines interesect at some point
 */
bool Line::operator&(const Line &l)
{
    Point a = this->_points[FST_POINT], b = this->_points[SEC_POINT],
            c = l._points[FST_POINT], d = l._points[SEC_POINT];
    CordType s, t;
    CordType s1_x = b.getX() - a.getX(), s1_y = b.getY() - a.getY(),
             s2_x = d.getX() - c.getX(), s2_y = d.getY() - c.getY();

    s = (-s1_y * (a.getX() - c.getX()) + s1_x * (a.getY() - c.getY())) /
        (-s2_x * s1_y + s1_x * s2_y);

    t = ( s2_x * (a.getY() - c.getY()) - s2_y * (a.getX() - c.getX())) /
        (-s2_x * s1_y + s1_x * s2_y);

    return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}
