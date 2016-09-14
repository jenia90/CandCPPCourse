

#ifndef LINE_H
#define LINE_H

#include "Point.h"
#include "Defs.h"

#define SQUARE(x) ((x) * (x))

class Line {
    Point _points[2];

    bool isEqual(const Line& l);
public:
    Line(Point& a, Point& b);
    ~Line();

    const std::string name = "Line";
    
    Point *getPoints(){ return _points; }
    CordType getLength() const;
    CordType getSlope() const;

    bool operator||(const Line& l);
    Line&operator=(const Line& l);
    bool operator ==(const Line& l);
    bool operator !=(const Line& l);
    bool operator&(const Line& l);
};


#endif //LINE_H
