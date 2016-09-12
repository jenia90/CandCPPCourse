//
// Created by jenia on 11/09/2016.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Point.h"

class Shape {
	std::vector<Point> _points;
	int _numOfSides;
public:
	//Shape(std::strind shapeLine);
    Shape(std::__cxx11::string shapeLine);
	Shape(Shape& shape);
	~Shape();
};


#endif //SHAPE_H
