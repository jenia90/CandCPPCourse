

#include <cmath>
#include "Trapezoid.h"

Trapezoid::Trapezoid(std::vector<Point> &_points, std::vector<Line> &_edges) : Shape(_points, _edges)
{
}

CordType Trapezoid::calculateArea()
{
    Line b1 = getEdges()[0], b2 = getEdges()[2];
    CordType height = fabs(b1.getPoints()->getX() - b2.getPoints()->getX());

    return (b1.getLength() + b2.getLength()) * height / 2;
}

void Trapezoid::printShape()
{
    printTrapez(getPoints()[0].getX(), getPoints()[0].getY(),
                getPoints()[1].getX(), getPoints()[1].getY(),
                getPoints()[2].getX(), getPoints()[2].getY(),
                getPoints()[3].getX(), getPoints()[3].getY());
}

std::shared_ptr<Trapezoid> Trapezoid::createTrapezoid(std::vector<Point> &_points)
{

    if(_points.size() != 4)
    {
        return false;
    }

    std::vector<Line> edges;
    edges = ShapeUtils::createEdges(_points);

    if(edges[0].getSlope() >= EPSILON && edges[2].getSlope() >= EPSILON)
    {
        ShapeUtils::exitWithError(TRAPEZOID_ERROR);
    }
    else if(_points[0].getY() == _points[2].getY())
    {
        ShapeUtils::exitWithError(TRAPEZOID_ERROR);
    }
    return std::make_shared<Trapezoid>(_points, edges);
}
