

#ifndef TRIANGLE_H
#define TRIANGLE_H


#define TRIANGLE_VERT_ERROR "Invalid triangle! Triangle vertices cannot be on the same line or be" \
                            " the same point."

#include "Shape.h"
#include "ShapeUtils.h"

class Triangle : public Shape
{
public:
    const std::string name = "Triangle";
    Triangle(std::vector<Point> &_points, std::vector<Line> &_edges);

    virtual CordType calculateArea();
    virtual void printShape() final;

    static std::shared_ptr<Triangle> createTriangle(std::vector<Point> &_points);
};


#endif //TRIANGLE_H
