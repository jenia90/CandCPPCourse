//
// Created by jenia on 11/09/2016.
//

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

using namespace std;

class Shape {
	int _numOfSides;
	vector<double> *_sides;
public:
    Shape(int numOfSides);
	Shape(Shape& shape);
	~Shape();
};


#endif //SHAPE_H
