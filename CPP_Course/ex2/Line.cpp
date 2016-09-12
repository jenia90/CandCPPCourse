//
// Created by jenia on 13/09/2016.
//

#include "Line.h"

Point Line::operator&(Line &l)
{
    double s, t;
    Point a = this->points[0], b = this->points[1], c = l.getPoints()[0], d = l.getPoints()[1];
    Point interP;
    Point s1, s2;

    s1.set(b.getX() - a.getX(), b.getY() - a.getY());
    s2.set(d.getX() - c.getX(), d.getY() - c.getY());

    s = (-s1.getY() * (a.getX() - c.getX()) + s1.getX() * (a.getY() - c.getY())) /
            (-s2.getX() * s1.getY() + s1.getX() * s2.getY());

    t = ( s2.getX() * (a.getY() - c.getY()) - s2.getY() * (a.getX() - c.getX())) /
            (-s2.getX() * s1.getY() + s1.getX() * s2.getY());

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        interP.set(a.getX() + (t * s1.getX()), a.getY() + (t * s1.getY()));
    }

    return interP; // No collision
}