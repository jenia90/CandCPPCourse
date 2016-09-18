/**
 * @file Triangle.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the Triangle class and its members
 * @section DESCRIPTION:
 * This class represents a Triangle in 2D space.
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#define TRIANGLE_VERT_ERROR "Invalid triangle! Triangle vertices cannot be on the same line or be" \
                            " the same point."

#define DEF_NUM_POINTS_TRI 3

#include "Shape.h"
#include "ShapeUtils.h"

class Triangle : public Shape
{
public:
    const std::string name = "Triangle";
    /**
     * @brief ctor
     * @param _points vector container of Point objects
     * @param _edges vector container of Line objects
     */
    Triangle(std::vector<Point> &_points, std::vector<Line> &_edges);

    /**
     * @brief Calculates the area of a triangle
     * @return Area of a triangle as CordType type
     */
    virtual CordType calculateArea();

    /**
     * @brief Prints the shape representation (it's points)
     */
    virtual void printShape() final;

    /**
     * @brief Static helper method to which validates the passed in reference to Point array and
     * if all went well returns a pointer to a new Triangle object.
     * @param _points vector container of Point objects
     * @return new Triangle shared_ptr object if successful; otherwise exists the program.
     */
    static std::shared_ptr<Triangle> getTriangle(std::vector<Point> &_points);
};


#endif //TRIANGLE_H
