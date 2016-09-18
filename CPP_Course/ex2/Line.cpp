

#include <cmath>
#include "Line.h"

Line::Line(Point &a, Point &b)
{
    _points[0] = a;
    _points[1] = b;
}

Line::~Line()
{
}


CordType Line::getLength() const
{
    CordType len = sqrt(SQUARE(_points[1].getX() - _points[0].getX()) +
                   SQUARE(_points[1].getY() - _points[0].getY()));
    return len;
}

CordType Line::getSlope() const
{
    return fabs((_points[1].getY() - _points[0].getY()) / (_points[1].getX() - _points[0].getX()));
}

bool Line::operator||(const Line &l)
{
    return fabs(this->getSlope() - l.getSlope()) < EPSILON;
}

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

bool Line::isEqual(const Line& l)
{
    return (_points[0] == l._points[0]) && (_points[1] == l._points[1]);
}

bool Line::operator==(const Line& l)
{
    return isEqual(l);
}

bool Line::operator !=(const Line& l)
{
    return !isEqual(l);
}

bool Line::operator&(const Line &l)
{
    Point a = this->_points[0], b = this->_points[1], c = l._points[0], d = l._points[1];
    CordType s, t;
    CordType s1_x = b.getX() - a.getX(), s1_y = b.getY() - a.getY(),
             s2_x = d.getX() - c.getX(), s2_y = d.getY() - c.getY();

    s = (-s1_y * (a.getX() - c.getX()) + s1_x * (a.getY() - c.getY())) /
        (-s2_x * s1_y + s1_x * s2_y);

    t = ( s2_x * (a.getY() - c.getY()) - s2_y * (a.getX() - c.getX())) /
        (-s2_x * s1_y + s1_x * s2_y);

    return s >= 0 && s <= 1 && t >= 0 && t <= 1;
}
