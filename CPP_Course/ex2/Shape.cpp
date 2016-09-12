//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"

Shape::Shape(std::vector<Point> points) : _points(points)
{
    if(!validateShape(_points))
    {
        printError();
    }
}

Shape::Shape(Shape &shape)
{

}

Shape::~Shape()
{

}

int Shape::orientation(Point a, Point b, Point c)
{
    int val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
              (b.getX() - a.getX()) * (c.getY() - b.getY());

    if (val == COLLINEAR)
    {
        return COLLINEAR;
    }
    return (val > COLLINEAR)? CLOCKWISE: COUNTERCLOCKWISE;
}