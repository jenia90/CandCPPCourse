/**
 * @file Shape.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the Shape class and its members
 * @section DESCRIPTION:
 * Abstract class of a shape. It support such actions as checking for intersects of 2 shapes,
 * initializing the shape's edges and holds the shape factory static method.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <memory>
#include <iostream>
#include "PrintOuts.h"
#include "Defs.h"
#include "Line.h"

#define FST_POINT 0
#define SEC_POINT 1
#define TRD_POINT 2
#define FOUR_POINT 3

class Shape
{
    std::vector<Point> _vertices;
    std::vector<Line> _edges;

    /**
     * @brief helper method to check for intersection of shapes using point orientation,
     * @param shp Shape object reference
     * @return true if shapes intersect; false otherwise.
     */
    bool pointIntersect(const Shape& shp);

    /**
     * @brief helper method to check for intersection of shapes by checking if their edges intersect
     * @param shp Shape object reference
     * @return true if shapes intersect; false otherwise.
     */
    bool lineIntersect(const Shape& shp);

public:

    /**
     * @brief ctor. given an array of Point objects inits the shape
     * @param points Point object vector container
     */
    Shape(std::vector<Point> &_points, std::vector<Line> &_edges);

    /**
     * dtor
     */
    ~Shape();

    /**
     * Pure virtual method to calculate the area of a Shape.
     */
    virtual CordType calculateArea() = 0;

    /**
     * Pure virtual method which prints the shape
     */
    virtual void printShape() = 0;

    /**
     * @brief Getter for the shape vertices
     * @return vector container of Point objects
     */
	std::vector<Point> getPoints() const
	{
		return _vertices;
	}

    /**
     * @brief Getter for the shape edges.
     * @return vector container of Line objects
     */
    std::vector<Line> getEdges() const
    {
        return _edges;
    }

    /**
     * @brief Overload of & operator to check for shape intersect
     * @param shp second Shape object reference
     * @return true if shapes intersect; false otherwise
     */
    bool operator&(const Shape& shp);

    /**
     * @brief Shape object factory method. Given a type char and array of points returns a new
     * shape of given type.
     * @param type type of the shape
     * @param points vector container of Point objects which create the shape
     * @return Shape object pointer.
     */
    static std::shared_ptr<Shape> getShape(char type, std::vector<Point> &points);
};


#endif //SHAPE_H
