//
// Created by jenia on 11/09/2016.
//

#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Shape.h"
#include "ShapeUtils.h"

#define TRAPEZOID_ERROR "Invalid trapezoid! Trapezoid vertices cannot be on the same line or  be "\
                        "the same point.\n Also, make sure its bases are parallel to X axis."

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

    static std::shared_ptr<Trapezoid> createTrapezoid(std::vector<Point> &_points);
};


#endif //TRAPEZOID_H
