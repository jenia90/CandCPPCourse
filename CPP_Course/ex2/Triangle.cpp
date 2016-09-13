

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
