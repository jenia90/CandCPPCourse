//
// Created by jenia on 13/09/2016.
//

#ifndef CANDCPPCOURSE_LINE_H
#define CANDCPPCOURSE_LINE_H


#include "Point.h"

class Line {
    Point points[2];
public:
    Line(Point _points[2]);
    Line(Point& a, Point& b);
    ~Line();

    Point *getPoints(){ return points; }

    Point operator&(Line& l);
};


#endif //CANDCPPCOURSE_LINE_H
