//
// Created by jenia on 11/09/2016.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Point.h"

#define COLLINEAR 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2

class Shape {
protected:
	std::vector<Point> _points;

	int orientation(Point a, Point b, Point c);

    virtual bool validateShape(std::vector<Point> points) = 0;
	virtual void printError() = 0;
public:
    Shape();
    Shape(std::vector<Point> points);
	Shape(Shape& shape);
	~Shape();

	std::vector<Point> getPoints() const
	{
		return _points;
	}
};


#endif //SHAPE_H
