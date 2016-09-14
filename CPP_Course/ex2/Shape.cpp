//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"

Shape::Shape(std::vector<Point> &points) : _vertices(points)
{
    _edges = initEdges(points);
    /*if(!validateShape(_vertices))
    {
        exitWithError();
    }*/
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

bool Shape::operator&(const Shape &shp)
{
    for(Point p : shp.getPoints())
    {
        for (size_t i = 0; i < _vertices.size(); ++i) {
            if(orientation(_vertices[i], _vertices[i + 1], p) == CLOCKWISE)
            {
                return true;
            }
        }
    }

    return false;
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

void Shape::exitWithError()
{
    std::cerr << TYPE_CHAR_ERROR << std::endl;
    exit(EXIT_FAILURE);
}

Shape* Shape::createShape(char type, std::vector<Point> &points)
{
    switch (type)
    {
        case 't':
            return new Triangle(points);
        case 'T':
            return new Trapezoid(points);
        default:
            exit(EXIT_FAILURE);
            //exitWithError();
    }
}
