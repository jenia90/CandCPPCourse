//
// Created by jenia on 11/09/2016.
//

#ifndef TRAPEZOID_H
#define TRAPEZOID_H

#include "Shape.h"

#define TRAPEZOID_ERROR "Invalid trapezoid! Trapezoid vertices cannot be on the same line or  be "\
                        "the same point.\n Also, make sure its bases are parallel to X axis."

class Trapezoid : protected Shape
{
    Trapezoid(std::vector<Point> _points);
    bool validateShape(std::vector<Point> points);
    void exitWithError();
};


#endif //TRAPEZOID_H
