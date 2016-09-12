//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"

Shape::Shape(std::vector<Point> points) : _vertices(points)
{
    if(!validateShape(_vertices))
    {
        printError();
    }

    for (int i = 0; i < _vertices.size(); ++i) {
        _edges[i] = Line(_vertices[i], _vertices[(i+1)%_vertices.size()]);
    }
}

Shape::Shape(Shape &shape)
{
    if(!validateShape(_vertices = shape.getPoints()))
    {
        printError();
    }
}

Shape::~Shape()
{
    _vertices.clear();
}

int Shape::orientation(Point a, Point b, Point c)
{
    double val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
              (b.getX() - a.getX()) * (c.getY() - b.getY());

    if (val == COLLINEAR)
    {
        return COLLINEAR;
    }
    return (val > COLLINEAR)? CLOCKWISE: COUNTERCLOCKWISE;
}

std::vector<Point> Shape::operator&(const Shape &shp) {
    std::vector<Point> intersectVec;

    for(Point p : shp.getPoints())
    {
        for (int i = 0; i < _vertices.size(); ++i) {
            if(orientation(_vertices[i], _vertices[i+1], p) == CLOCKWISE);

        }
    }

}
