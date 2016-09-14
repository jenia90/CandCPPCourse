

#include <cmath>
#include "Trapezoid.h"

Trapezoid::Trapezoid(std::vector<Point> &_points) : Shape(_points)
{
    if(!validateShape(_points))
    {
        exitWithError();
    }
}

bool Trapezoid::validateShape(std::vector<Point> &points)
{

    if(points.size() != 4)
    {
        return false;
    }
    else if(_edges[0].getSlope() >= EPSILON && _edges[2].getSlope() >= EPSILON)
    {
        return false;
    }
    return true;
}

void Trapezoid::exitWithError()
{
    std::cerr << TRAPEZOID_ERROR << std::endl;
    exit(EXIT_FAILURE);
}

CordType Trapezoid::calculateArea()
{
    Line b1 = _edges[0], b2 = _edges[2];
    CordType height = fabs(b1.getPoints()->getX() - b2.getPoints()->getX());

    return (b1.getLength() + b2.getLength()) * height / 2;
}

void Trapezoid::printShape()
{
    printTrapez(_vertices[0].getX(), _vertices[0].getY(), _vertices[1].getX(), _vertices[1].getY
            (), _vertices[2].getX(), _vertices[2].getY(), _vertices[3].getX(), _vertices[3].getY());
}
