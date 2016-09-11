/**
 * @file PointSetBinaryOperations.cpp
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Program to print the result of some binary operations on PointSet objects
 * @section DESCRIPTION:
 * This is a driver class which generates 2 sets of points using helper method and then applies 
 * some binary operations from the PointSet class on them.
 * Output: The result of running the various operations
 */

#include <iostream>
#include "PointSet.h"

#define TITLE_MSG "Checking operators on 2 generate sets: up to 10 and up to 5: "
#define EQUAL_TITLE "result for '==': "
#define NOT_EQUAL_TITLE "result for '!=': "
#define SUBTRACT_TITLE "result for '-':"
#define INTERSECT_TITLE "result for '&':"
#define TRUE "true"
#define FALSE "false"

/**
 * @brief Helper function used to generate a set of points given the limit on coordinates
 * @param pointSet A PointSet object reference to which we will add the Points.
 * @param lim limit for the point coordinates (default: 10)
 */
void generatePointSet(PointSet& pointSet, int lim = 10)
{
    for (int i = -1 * lim; i <= lim; i++)
    {
        for (int j = -1 * lim; j <= lim; j++)
        {
            pointSet.add(Point(i, j));
        }
    }
    pointSet.add(Point(0, lim + 1));
    pointSet.add(Point(0, (-1 * lim) - 1));
    pointSet.add(Point(lim + 1, 0));
    pointSet.add(Point((-1 * lim) - 1, 0));
}

/**
 * @brief Helper function to print the binary value
 * @param val value to print
 * @return "true" if true and "false" if false
 */
std::string printBinary(bool val)
{
    return val ? TRUE : FALSE;
}

int main()
{
    PointSet pointSet1, pointSet2;
    generatePointSet(pointSet1), generatePointSet(pointSet2, 5);

    PointSet subtract = pointSet1 - pointSet2;
    PointSet intersect = pointSet1 & pointSet2;

    std::cout << TITLE_MSG << std::endl;
    std::cout << EQUAL_TITLE << printBinary(pointSet1 == pointSet2) << std::endl;
    std::cout << NOT_EQUAL_TITLE << printBinary(pointSet1 != pointSet2) << std::endl;
    std::cout << SUBTRACT_TITLE << std::endl << subtract.toString() << std::endl;
    std::cout << INTERSECT_TITLE << std::endl << intersect.toString() << std::endl;

}