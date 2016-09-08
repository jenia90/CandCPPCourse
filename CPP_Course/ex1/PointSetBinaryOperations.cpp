//
// Created by jenia on 06/09/2016.
//

#include "PointSet.h"

PointSet myRun()
{
    PointSet pointSet;
    int lim = 50;
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

int main()
{

}