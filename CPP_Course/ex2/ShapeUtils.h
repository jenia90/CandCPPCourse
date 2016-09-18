/**
 * @file Point.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the ShapeUtils class and its members
 * @section DESCRIPTION:
 * This is a static class which contains utility methods for other Shape related classes.
 */

#ifndef SHAPEUTILS_H
#define SHAPEUTILS_H

#include <string>
#include <vector>
#include "Point.h"
#include "Line.h"

class ShapeUtils
{
public:
    /**
     * Point orientation enum
     */
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
     * Prints an error message and exits the program
     * @param msg Message to print
     * @param _points Point object vector to clear before exit
     * @param _edges Line object vector to clear before exit
     */
    static void exitWithError(std::string msg, std::vector<Point> &_points, std::vector<Line> &_edges);
};
#endif //CANDCPPCOURSE_SHAPEUTILS_H
