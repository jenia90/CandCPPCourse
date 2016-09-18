

#ifndef TRIANGLE_H
#define TRIANGLE_H


#define TRIANGLE_VERT_ERROR "Invalid triangle! Triangle vertices cannot be on the same line or be" \
                            " the same point."

#include "Shape.h"

class Triangle : public Shape
{
protected:
    virtual void exitWithError();

public:
    Triangle(std::vector<Point> &_points);
    virtual bool validateShape(std::vector<Point> &points);

    const std::string name = "Triangle";

    virtual CordType calculateArea();
    virtual void printShape() final;
};


#endif //TRIANGLE_H
