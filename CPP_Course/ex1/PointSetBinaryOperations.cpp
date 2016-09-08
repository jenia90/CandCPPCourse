//
// Created by jenia on 06/09/2016.
//

#include <iostream>
#include "PointSet.h"

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

    std::cout << "Checking operators on 2 generate sets: up to 50 and up to 40: " << std::endl;
    std::cout << "result for '==': " << printBinary(pointSet1==pointSet2) << std::endl;
    std::cout << "result for '!=': " << printBinary(pointSet1!=pointSet2) << std::endl;
    std::cout << "result for '-':" << std::endl << subtract.toString() << std::endl;
    std::cout << "result for '&':" << std::endl << intersect.toString() << std::endl;

}