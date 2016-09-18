

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "PrintOuts.h"
#include "Defs.h"
#include "Point.h"
#include "Line.h"

#define COLLINEAR 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2

#define TYPE_CHAR_ERROR "Wrong type character passed!"

class Shape {
public:
	std::vector<Point> _vertices;
	std::vector<Line> _edges;

    /**
     * @brief Gets the orientation of 3 points in respect to each other
     * @param a Point object
     * @param b Point object
     * @param c Point object
     * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
     */
	int orientation(Point a, Point b, Point c);
    std::vector<Line> initEdges(std::vector<Point> &vertices);
    virtual void exitWithError() = 0;

    /**
     * @brief A function used to validate a set of points and check if it's valid for a given shape
     * @param points Point object vector
     * @return true if valid; false otherwise.
     */
    virtual bool validateShape(std::vector<Point> &points) = 0;
    Shape(std::vector<Point> &points);
	~Shape();

    virtual CordType calculateArea() = 0;
    virtual void printShape() = 0;

	std::vector<Point> getPoints() const
	{
		return _vertices;
	}

    std::vector<Line> getEdges() const
    {
        return _edges;
    }

    bool operator&(const Shape& shp);

    bool pointIntersect(const Shape& shp);
    bool lineIntersect(const Shape& shp);

    static Shape* createShape(char type, std::vector<Point> &points);
};


#endif //SHAPE_H
