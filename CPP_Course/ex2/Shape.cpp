//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"

Shape::Shape(std::vector<Point> &points) : _vertices(points)
{
    _edges = initEdges(points);
}

Shape::~Shape()
{
    _vertices.clear();
    _edges.clear();
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

bool Shape::pointIntersect(const Shape& shp)
{
    bool isClockWise = false;
    for(Point p : shp.getPoints())
    {
        for (size_t i = 0; i < _vertices.size(); ++i)
        {
            isClockWise = orientation(_vertices[i], _vertices[(i + 1) % _vertices.size()], p)
                          != COUNTERCLOCKWISE;
        }

        if(isClockWise)
        {
            return true;
        }
    }

    return false;
}

bool Shape::lineIntersect(const Shape &shp)
{
    for(Line &l1 : shp.getEdges())
    {
        for(Line &l2 : _edges)
        {
            if(l1 & l2)
            {
                return true;
            }
        }
    }

    return false;
}

bool Shape::operator&(const Shape &shp)
{
    if(lineIntersect(shp))
        return true;

    return pointIntersect(shp);
}

std::vector<Line> Shape::initEdges(std::vector<Point> &vertices)
{
    std::vector<Line> edges;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Line l = Line(vertices[i], vertices[(i + 1) % vertices.size()]);
        if(l.getLength() == 0)
        {
            exitWithError();
        }
        edges.push_back(l);
    }

    return edges;
}

Shape* Shape::createShape(char type, std::vector<Point> &points)
{
    switch (type)
    {
        case 'T':
            return new Triangle(points);
        case 't':
            return new Trapezoid(points);
        default:
            std::cerr << TYPE_CHAR_ERROR << std::endl;
            exit(EXIT_FAILURE);
    }
}
