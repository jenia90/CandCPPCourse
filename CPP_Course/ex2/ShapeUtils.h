//
// Created by jenia on 18/09/2016.
//

#ifndef SHAPEUTILS_H
#define SHAPEUTILS_H

#include <string>
#include <vector>
#include "Point.h"
#include "Line.h"

class ShapeUtils
{
public:
    enum Orientation
    {
        Collinear,
        Clockwise,
        Counterclockwise
    };
    /**
     * @brief given a vector container of Points returns a vector container of Lines created by
     * these points.
     * @param vertices vector container of Point objects
     * @return vector container of Line objects
     */
    static std::vector<Line> createEdges(std::vector<Point> &vertices);

    /**
     * @brief Gets the orientation of 3 points in respect to each other
     * @param a Point object
     * @param b Point object
     * @param c Point object
     * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
     */
    static int orientation(Point a, Point b, Point c);

    /**
     * Pure virtual method, if error occured, prints the error to std::cerr and exists with
     * EXIT_FAILURE code
     */
    static void exitWithError(std::string msg);
};
#endif //CANDCPPCOURSE_SHAPEUTILS_H
