

#include <cmath>
#include "Triangle.h"


Triangle::Triangle(std::vector<Point> &_points, std::vector<Line> &_edges) : Shape(_points, _edges)
{
}

CordType Triangle::calculateArea()
{
    Point p1 = getPoints()[0], p2 = getPoints()[1], p3 = getPoints()[2];

    return fabs((p1.getX() * p2.getY() + p1.getY() * p3.getX() + p2.getX() * p3.getY() -
            (p3.getX() * p2.getY() + p1.getY() * p2.getX() + p3.getY() * p1.getX())) / 2);
}

void Triangle::printShape()
{
    printTrig(getPoints()[0].getX(), getPoints()[0].getY(), getPoints()[1].getX(),
              getPoints()[1].getY(), getPoints()[2].getX(), getPoints()[2].getY());
}

std::shared_ptr<Triangle> Triangle::createTriangle(std::vector<Point> &_points)
{
    if(_points.size() != 3)
    {
        ShapeUtils::exitWithError(TRIANGLE_VERT_ERROR);
    }
    else if(ShapeUtils::orientation(_points[0], _points[1], _points[2]) == ShapeUtils::Collinear)
    {
        ShapeUtils::exitWithError(TRIANGLE_VERT_ERROR);
    }

    std::vector<Line> edges;
    edges = ShapeUtils::createEdges(_points);

    return std::make_shared<Triangle>(_points, edges);
}
