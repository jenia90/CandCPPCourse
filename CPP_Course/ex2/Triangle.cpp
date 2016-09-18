

#include <cmath>
#include "Triangle.h"


/**
 * @brief ctor
 * @param _points vector container of Point objects
 * @param _edges vector container of Line objects
 */
Triangle::Triangle(std::vector<Point> &_points, std::vector<Line> &_edges) : Shape(_points, _edges)
{
}

/**
 * @brief Calculates the area of a triangle
 * @return Area of a triangle as CordType type
 */
CordType Triangle::calculateArea()
{
    Point p1 = getPoints()[FST_POINT], p2 = getPoints()[SEC_POINT], p3 = getPoints()[TRD_POINT];

    return fabs((p1.getX() * p2.getY() + p1.getY() * p3.getX() + p2.getX() * p3.getY() -
            (p3.getX() * p2.getY() + p1.getY() * p2.getX() + p3.getY() * p1.getX())) / 2);
}

/**
 * @brief Prints the shape representation (it's points)
 */
void Triangle::printShape()
{
    printTrig(getPoints()[FST_POINT].getX(), getPoints()[FST_POINT].getY(),
              getPoints()[SEC_POINT].getX(), getPoints()[SEC_POINT].getY(),
              getPoints()[TRD_POINT].getX(), getPoints()[TRD_POINT].getY());
}

/**
 * @brief Static helper method to which validates the passed in reference to Point array and
 * if all went well returns a pointer to a new Triangle object.
 * @param _points vector container of Point objects
 * @return new Triangle shared_ptr object if successful; otherwise exists the program.
 */
std::shared_ptr<Triangle> Triangle::createTriangle(std::vector<Point> &_points)
{
    std::vector<Line> edges;
    if(_points.size() != DEF_NUM_POINTS_TRI)
    {
        ShapeUtils::exitWithError(TRIANGLE_VERT_ERROR, _points, edges);
    }
    else if(ShapeUtils::orientation(_points[FST_POINT], _points[SEC_POINT], _points[TRD_POINT]) ==
            ShapeUtils::Collinear)
    {
        ShapeUtils::exitWithError(TRIANGLE_VERT_ERROR, _points, edges);
    }

    edges = ShapeUtils::createEdges(_points);

    return std::make_shared<Triangle>(_points, edges);
}
