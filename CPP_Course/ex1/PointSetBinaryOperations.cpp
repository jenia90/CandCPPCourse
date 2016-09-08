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

#define TITLE_MSG "Checking operators on 2 generate sets: up to 50 and up to 40: "
#define EQUAL_TITLE "result for '==': "
#define NOT_EQUAL_TITLE "result for '!=': "
#define SUBTRACT_TITLE "result for '-':"
#define INTERESECT_TITLE "result for '&':"

PointSet generatePointSet(int lim = 10)
{
    PointSet pointSet;
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
    return pointSet;
}

std::string printBinary(bool val)
{
    return val ? "true" : "false";
}

int main()
{
    PointSet pointSet1 = generatePointSet(), pointSet2 = generatePointSet(5);
    PointSet subtract = (pointSet1 - pointSet2);
    PointSet intersect = (pointSet1 & pointSet2);

    std::cout << TITLE_MSG << std::endl;
    std::cout << EQUAL_TITLE << printBinary(pointSet1==pointSet2) << std::endl;
    std::cout << NOT_EQUAL_TITLE << printBinary(pointSet1!=pointSet2) << std::endl;
    std::cout << SUBTRACT_TITLE << std::endl << subtract.toString() << std::endl;
    std::cout << INTERESECT_TITLE << std::endl << intersect.toString() << std::endl;

}