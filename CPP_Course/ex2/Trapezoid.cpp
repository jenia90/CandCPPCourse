

#include "Trapezoid.h"

Trapezoid::Trapezoid(std::vector<Point> _points) : Shape(_points)
{
}

bool Trapezoid::validateShape(std::vector<Point> points)
{

    if(points.size() != 4)
    {
        return false;
    }
    else if(_edges[0].getSlope() == 0 && _edges[2].getSlope() == 0)
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
