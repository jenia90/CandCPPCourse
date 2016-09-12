//
// Created by jenia on 11/09/2016.
//

#include "Shape.h"

Shape::Shape(int numOfSides) :_numOfSides(numOfSides), _sides(new std::vector<double>[numOfSides])
{
}

Shape::Shape(Shape& shape)
{
}

Shape::~Shape()
{
}
