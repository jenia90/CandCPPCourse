//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "ShapeUtils.h"

Shape::Shape(std::vector<Point> &_points, std::vector<Line> &_edges) : _vertices(_points), _edges
        (_edges)
{
}

Shape::~Shape()
{
    _vertices.clear();
    _edges.clear();
}

bool Shape::pointIntersect(const Shape& shp)
{
    for(Point p : shp.getPoints())
    {
        int initOrientation = ShapeUtils::orientation(_vertices[0], _vertices[1], p);
        for (size_t i = 1; i < _vertices.size(); ++i)
        {
            if((ShapeUtils::orientation(_vertices[i], _vertices[(i + 1) % _vertices.size()], p)
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

std::shared_ptr<Shape> Shape::createShape(char type, std::vector<Point> &points)
{
    switch (type)
    {
        case 'T':
            return Triangle::createTriangle(points);
        case 't':
            return Trapezoid::createTrapezoid(points);
        default:
            std::cerr << TYPE_CHAR_ERROR << std::endl;
            exit(EXIT_FAILURE);
    }
}
