//
// Created by jenia on 18/09/2016.
//

#include <iostream>
#include "ShapeUtils.h"

/**
 * @brief Gets the orientation of 3 points in respect to each other
 * @param a Point object
 * @param b Point object
 * @param c Point object
 * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
 */
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

/**
 * @brief given a vector container of Points returns a vector container of Lines created by
 * these points.
 * @param vertices vector container of Point objects
 * @return vector container of Line objects
 */
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

/**
 * Prints an error message and exits the program
 * @param msg Message to print
 * @param _points Point object vector to clear before exit
 * @param _edges Line object vector to clear before exit
 */
void ShapeUtils::exitWithError(std::string msg, std::vector<Point> &_points, std::vector<Line> &_edges)
{
    _points.clear();
    _edges.clear();
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}
