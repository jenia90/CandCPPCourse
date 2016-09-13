

#ifndef TRIANGLE_H
#define TRIANGLE_H


#define TRIANGLE_VERT_ERROR "Invalid triangle! Triangle vertices cannot be on the same line or be" \
                            " the same point."

#include "Shape.h"

class Triangle : protected Shape
{
protected:
    Triangle(std::vector<Point> _points);
    bool validateShape(std::vector<Point> points);
    void exitWithError();
};


#endif //TRIANGLE_H
