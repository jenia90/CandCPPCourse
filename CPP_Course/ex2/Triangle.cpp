

#include <cmath>
#include "Triangle.h"


Triangle::Triangle(std::vector<Point> _points) : Shape(_points)
{
}

bool Triangle::validateShape(std::vector<Point> points)
{
    if(points.size() != 3)
    {
        return false;
    }
    else if(orientation(points[0], points[1], points[2]) == COLLINEAR)
    {
        return false;
    }
    return true;
}

void Triangle::exitWithError()
{
    std::cerr << TRIANGLE_VERT_ERROR << std::endl;
    exit(EXIT_FAILURE);
}

CordType Triangle::calculateArea()
{
    Point p1 = _vertices[0], p2 = _vertices[1], p3 = _vertices[2];

    return fabs((p1.getX() * p2.getY() + p1.getY() * p3.getX() + p2.getX() * p3.getY() -
            (p3.getX() * p2.getY() + p1.getY() * p2.getX() + p3.getY() * p1.getX())) / 2);
}

void Triangle::printShape()
{
    printTrig(_vertices[0].getX(), _vertices[0].getY(), _vertices[1].getX(), _vertices[1].getY
            (), _vertices[2].getX(), _vertices[2].getY());
}
