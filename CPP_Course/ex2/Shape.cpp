/**
 * @file Point.h
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Header file containg the declarations of the Point class and its members
 * @section DESCRIPTION:
 * This class represents a point in 2D space.
 */

#include "Shape.h"
#include "Triangle.h"
#include "Trapezoid.h"

/**
 * @brief ctor. given an array of Point objects inits the shape
 * @param points Point object vector container
 */
Shape::Shape(std::vector<Point> &_points, std::vector<Line> &_edges) : _vertices(_points),
                                                                       _edges(_edges)
{
}

/**
 * dtor
 */
Shape::~Shape()
{
    _vertices.clear();
    _edges.clear();
}

/**
 * @brief helper method to check for intersection of shapes using point orientation,
 * @param shp Shape object reference
 * @return true if shapes intersect; false otherwise.
 */
bool Shape::pointIntersect(const Shape& shp)
{
    for(Point p : shp.getPoints())
    {
        int o, initOrient = ShapeUtils::orientation(_vertices[FST_POINT], _vertices[SEC_POINT],
                                                      p);
        for (size_t i = SEC_POINT; i < _vertices.size(); ++i)
        {
            o = ShapeUtils::orientation(_vertices[i], _vertices[(i + 1) % _vertices.size()], p);
            if(o != initOrient)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief helper method to check for intersection of shapes by checking if their edges intersect
 * @param shp Shape object reference
 * @return true if shapes intersect; false otherwise.
 */
bool Shape::lineIntersect(const Shape &shp)
{
    for(Line &l1 : shp.getEdges())
    {
        for(Line &l2 : _edges)
        {
            if(l1 & l2)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief Overload of & operator to check for shape intersect
 * @param shp second Shape object reference
 * @return true if shapes intersect; false otherwise
 */
bool Shape::operator&(const Shape &shp)
{
    return pointIntersect(shp) || lineIntersect(shp);
}

/**
 * @brief Shape object factory method. Given a type char and array of points returns a new
 * shape of given type.
 * @param type type of the shape
 * @param points vector container of Point objects which create the shape
 * @return Shape object pointer.
 */
std::shared_ptr<Shape> Shape::createShape(char type, std::vector<Point> &points)
{
    switch (type)
    {
        case 'T':
            return Triangle::createTriangle(points);
        case 't':
            return Trapezoid::createTrapezoid(points);
        default:
            std::cerr << TYPE_CHAR_ERROR << std::endl;
            exit(EXIT_FAILURE);
    }
}
