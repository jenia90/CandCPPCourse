//
// Created by jenia on 11/09/2016.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H


#define TRIANGLE_VERT_ERROR "Invalid triangle! Triangle vertices cannot be on the same line or be" \
                            " the same point."

#include "Shape.h"

class Triangle : protected Shape
{
protected:
    Triangle(std::vector<Point> _points);
    virtual bool validateShape(std::vector<Point> points);
    virtual void printError();
};


#endif //TRIANGLE_H
