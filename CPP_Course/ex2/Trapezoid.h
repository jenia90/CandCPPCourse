/**
 * @file Triangle.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the Triangle class and its members
 * @section DESCRIPTION:
 * This class represents a Trapezoid in 2D space.
 */

#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Shape.h"
#include "ShapeUtils.h"

#define TRAPEZOID_ERROR "Invalid trapezoid! Trapezoid vertices cannot be on the same line or  be "\
                        "the same point.\n Also, make sure its bases are parallel to X axis."

#define DEF_NUM_POINT_TRAP 4
#define FST_BASE 0
#define SEC_BASE 2

class Trapezoid : public Shape
{
public:
    /**
     * Object name tag
     */
    const std::string name = "Trapezoid";

    /**
     * @brief ctor
     * @param _points Point object container which contains array of Points from which we create
     * the trapezoid
     */
    Trapezoid(std::vector<Point> &_points, std::vector<Line> &_edges);

    /**
     * @brief Calculates the area of a Trapezoid
     * @return area of this trapezoid.
     */
    virtual CordType calculateArea() final;

    /**
     * Prints this trapezoid
     */
    virtual void printShape() final;

    /**
     * @brief Static helper method to which validates the passed in reference to Point array and
     * if all went well returns a pointer to a new Trapezoid object.
     * @param _points vector container of Point objects
     * @return new Trapezoid shared_ptr object if successful; otherwise exists the program.
     */
    static std::shared_ptr<Trapezoid> createTrapezoid(std::vector<Point> &_points);
};


#endif //TRAPEZOID_H
