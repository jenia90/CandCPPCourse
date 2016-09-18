/**
 * @file Line.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the Line class and its members
 * @section DESCRIPTION:
 * This class represents a line between 2 points in 2D space.
 */

#ifndef LINE_H
#define LINE_H

#include <string>
#include "Point.h"
#include "Defs.h"

#define SQUARE(x) ((x) * (x))
#define FST_POINT 0
#define SEC_POINT 1

class Line
{
    Point _points[2];

    /**
     * @brief Helper method that checks if 2 lines are equal
     * @param l Line object ref
     * @return true if equal; false otherwise
     */
    bool isEqual(const Line& l);
public:
    /**
     * Ctor
     * @param a 1st Point object ref
     * @param b 2nd Point object ref
     */
    Line(Point& a, Point& b);

    /**
     * dtor
     */
    ~Line();

    const std::string name = "Line";

    /**
     * @brief Getter method for the points that represent this line
     * @return array of Point objects
     */
    Point *getPoints()
    {
        return _points;
    }

    /**
     * @brief Calculates the length of this line
     * @return length of the line in 2D space
     */
    CordType getLength() const;

    /**
     * @brief Calculates the slope of the line
     * @return slope of the line
     */
    CordType getSlope() const;

    /**
     * @brief Checks if 2 lines are parallel to each other (slope diff is in given margin)
     * @param l Line object ref
     * @return true if parallel; false otherwise
     */
    bool operator||(const Line& l);

    /**
     * Assignment operator.
     * @param l Line object reference
     * @return updated object reference
     */
    Line&operator=(const Line& l);

    /**
     * @brief is equal operator. Checks if 2 lines are equal
     * @param l Line object reference
     * @return true if equal; false otherwise
     */
    bool operator ==(const Line& l);

    /**
     * @brief is not equal operator. Checks if 2 lines are not equal
     * @param l Line object reference
     * @return true if not equal; false otherwise
     */
    bool operator !=(const Line& l);

    /**
     * @brief Intersection operator
     * @param l Line object reference
     * @return true if 2 lines interesect at some point
     */
    bool operator&(const Line& l);
};


#endif //LINE_H
