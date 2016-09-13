//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"

Shape::Shape(std::vector<Point> points) : _vertices(points)
{
    _edges = initEdges(points);
    if(!validateShape(_vertices))
    {
        exitWithError();
    }
}

Shape::Shape(Shape &shape)
{
    if(!validateShape(_vertices = shape.getPoints()))
    {
        exitWithError();
    }
}

Shape::~Shape()
{
    _vertices.clear();
}

int Shape::orientation(Point a, Point b, Point c)
{
    CordType val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
              (b.getX() - a.getX()) * (c.getY() - b.getY());

    if (val == COLLINEAR)
    {
        return COLLINEAR;
    }
    return (val > COLLINEAR)? CLOCKWISE: COUNTERCLOCKWISE;
}

bool Shape::operator&(const Shape &shp)
{
    int j = 0;
    for(Point p : shp.getPoints())
    {
        for (int i = 0; i < _vertices.size(); ++i) {
            if(orientation(_vertices[i], _vertices[i+1], p) == CLOCKWISE)
            {
                return true;
            }
        }
    }

    return false;
}

std::vector<Line> Shape::initEdges(std::vector<Point> vertices)
{
    std::vector<Line> edges;
    for (int i = 0; i < vertices.size(); ++i)
    {
        Line l = Line(vertices[i], vertices[(i + 1) % vertices.size()]);
        if(l.getLength() == 0)
        {
            exitWithError();
        }
        edges[i] = l;
    }

    return edges;
}
