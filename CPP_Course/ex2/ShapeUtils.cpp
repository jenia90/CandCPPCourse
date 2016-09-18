//
// Created by jenia on 18/09/2016.
//

#include <iostream>
#include "ShapeUtils.h"

int ShapeUtils::orientation(Point a, Point b, Point c)
{
    CordType val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
                   (b.getX() - a.getX()) * (c.getY() - b.getY());

    if (val == Collinear)
    {
        return Collinear;
    }
    return (val > Collinear)? Clockwise: Counterclockwise;
}



std::vector<Line> ShapeUtils::createEdges(std::vector<Point> &vertices)
{
    std::vector<Line> edges;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Line l = Line(vertices[i], vertices[(i + 1) % vertices.size()]);
        if(l.getLength() == 0)
        {
            edges.clear();
            return edges;
        }
        edges.push_back(l);
    }

    return edges;
}

void ShapeUtils::exitWithError(std::string msg)
{
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}
