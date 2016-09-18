

#include <cmath>
#include "Trapezoid.h"

/**
 * @brief ctor
 * @param _points Point object container which contains array of Points from which we create
 * the trapezoid
 */
Trapezoid::Trapezoid(std::vector<Point> &_points, std::vector<Line> &_edges) : Shape(_points, _edges)
{
}

/**
 * @brief Calculates the area of a Trapezoid
 * @return area of this trapezoid.
 */
CordType Trapezoid::calculateArea()
{
    Line b1 = getEdges()[FST_BASE], b2 = getEdges()[SEC_BASE];
    CordType height = fabs(b1.getPoints()->getY() - b2.getPoints()->getY());

    return (b1.getLength() + b2.getLength()) * height / 2;
}

/**
 * Prints this trapezoid
 */
void Trapezoid::printShape()
{
    printTrapez(getPoints()[FST_POINT].getX(), getPoints()[FST_POINT].getY(),
                getPoints()[SEC_POINT].getX(), getPoints()[SEC_POINT].getY(),
                getPoints()[TRD_POINT].getX(), getPoints()[TRD_POINT].getY(),
                getPoints()[FOUR_POINT].getX(), getPoints()[FOUR_POINT].getY());
}

/**
 * @brief Static helper method to which validates the passed in reference to Point array and
 * if all went well returns a pointer to a new Trapezoid object.
 * @param _points vector container of Point objects
 * @return new Trapezoid shared_ptr object if successful; otherwise exists the program.
 */
std::shared_ptr<Trapezoid> Trapezoid::getTrapezoid(std::vector<Point> &_points)
{

    if(_points.size() != DEF_NUM_POINT_TRAP)
    {
        return false;
    }

    std::vector<Line> edges;
    edges = ShapeUtils::createEdges(_points);

    if(edges[FST_BASE].getSlope() >= EPSILON && edges[SEC_BASE].getSlope() >= EPSILON)
    {
        ShapeUtils::exitWithError(TRAPEZOID_ERROR, _points, edges);
        return nullptr;
    }
    else if(_points[FST_BASE].getY() == _points[SEC_BASE].getY())
    {
        ShapeUtils::exitWithError(TRAPEZOID_ERROR, _points, edges);
        return nullptr;
    }
    return std::make_shared<Trapezoid>(_points, edges);
}