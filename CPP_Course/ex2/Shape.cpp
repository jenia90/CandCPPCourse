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
    for(Point p : shp.getPoints())
    {
        int initOrientation = orientation(_vertices[0], _vertices[1], p);
        for (size_t i = 1; i < _vertices.size(); ++i)
        {
            if((orientation(_vertices[i], _vertices[(i + 1) % _vertices.size()], p)
                              != initOrientation))
            {
                return false;
            }
        }
    }

    return true;
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
    return pointIntersect(shp) || lineIntersect(shp);
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

std::shared_ptr<Shape> Shape::createShape(char type, std::vector<Point> &points)
{
    switch (type)
    {
        case 'T':
            return std::make_shared<Triangle>(points);
        case 't':
            return std::make_shared<Trapezoid>(points);
        default:
            std::cerr << TYPE_CHAR_ERROR << std::endl;
            exit(EXIT_FAILURE);
    }
}
