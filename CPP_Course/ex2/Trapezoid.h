//
// Created by jenia on 11/09/2016.
//

#ifndef TRAPEZOID_H
#define TRAPEZOID_H


#include "Shape.h"

class Trapezoid : protected Shape
{
    Trapezoid(std::vector<Point> _points);
    virtual bool validateShape(_points);
};


#endif //TRAPEZOID_H
