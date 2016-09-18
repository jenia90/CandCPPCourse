//
// Created by jenia on 11/09/2016.
//

#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Shape.h"

#define TRAPEZOID_ERROR "Invalid trapezoid! Trapezoid vertices cannot be on the same line or  be "\
                        "the same point.\n Also, make sure its bases are parallel to X axis."

class Trapezoid : public Shape
{
protected:
    /**
     * Print an error message and exit with error code.
     */
    virtual void exitWithError();
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
    Trapezoid(std::vector<Point> &_points);

    /**
     * @brief Validates that the given set of points form a valid trapezoid
     * @param points reference to a vector container of Point objects
     * @return true if valid; false otherwise
     */
    virtual bool validateShape(std::vector<Point> &points);

    /**
     * @brief Calculates the area of a Trapezoid
     * @return area of this trapezoid.
     */
    virtual CordType calculateArea() final;

    /**
     * Prints this trapezoid
     */
    virtual void printShape() final;
};


#endif //TRAPEZOID_H
