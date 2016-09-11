/**
 * @file ConvexHull.cpp
 * @author jenia90
 * @version 1.0
 * @date 08 Sep 2016
 *
 * @brief Program for printing the convex hull of an unlimited set of points.
 * @section DESCRIPTION:
 *  This program waits for the user to enter unlimited number of points followed by the EOF char
 *  and then finds and prints the Convex Hull of those points using the Graham Scan algorithm
 *  implementation. More on this in the README file attached to the project.
 * Input: point coordinates followed by the enter and EOF char to end the input phase
 * Process: Adding the points to the PointSet, choosing a pivot with minimal Y coordinate and
 * then sorting the rest of the points using their polar angle in respect to the pivot point.
 * Then, using the Graham Scan algorithm we find the minimal Convex Hull of the set.
 * Output: sorted list of the convex hull points.
 */

#include <iostream>
#include <algorithm>
#include "Point.h"
#include "PointSet.h"

#define COLLINEAR 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2
#define TOP 1
#define NEXT_TO_TOP 2

#define RESULT "result:"
#define MIN_SCAN 3
#define NEXT_TO_PIVOT 1
#define PIVOT_INDEX 0
// Pivot point in respect to which we will do the comparisons and sorting.
Point p0;

/**
 * @brief Prints all the points which create the convex hull.
 * @param convex array of Point objects
 * @param size number of points in the array.
 */
void printConvex(PointSet& convex)
{
    std::cout << RESULT << std::endl << convex.toString();
}

/**
 * @brief Swaps to points
 * @param p1 Point 1
 * @param p2 Point 2
 */
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

/**
 * @brief Calculates the distance squared of 2 Points
 * @param p1 Point 1
 * @param p2 Point 2
 * @return product of multiplication
 */
int distanceSquared(Point p1, Point p2)
{
    return (p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
           (p1.getY() - p2.getY()) * (p1.getY() - p2.getY());
}

/**
 * @brief Calculates the orientation of 2 points in respect to the third one
 * @param p Point 1
 * @param q Point 2
 * @param r Point 3
 * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
 */
int orientation(Point a, Point b, Point c)
{
    int val = (b.getY() - a.getY()) * (c.getX() - b.getX()) -
              (b.getX() - a.getX()) * (c.getY() - b.getY());

    if (val == COLLINEAR)
    {
        return COLLINEAR;
    }
    return (val > COLLINEAR)? CLOCKWISE: COUNTERCLOCKWISE;
}

/**
 * @brief Helper function used to pass as a function pointer to the sort function for comparing
 * 2 Points.
 * @param a Point 1
 * @param a Point 2
 * @return
 */
int compare(Point a, Point b)
{
    int sort = orientation(p0, a, b);

    if (sort == COLLINEAR)
    {
        return distanceSquared(p0, a) <= distanceSquared(p0, b);
    }

    return (sort == COUNTERCLOCKWISE);
}

/**
 * @brief Implementation of graham scan algorithm to find the convex hull in a set of points.
 * @param pSet PointSet object reference containing all the points.
 * @param cHull PointSet object reference which will hold the points creating the convex.
 */
void grahamScan(const PointSet& pSet, PointSet& cHull)
{
    cHull.add(p0);
    cHull.add(pSet.getSet()[TOP]);
    cHull.add(pSet.getSet()[NEXT_TO_TOP]);

    for(int i = MIN_SCAN; i < pSet.size(); i++)
    {
        Point p = pSet.getSet()[i];
        while(orientation(cHull.getSet()[cHull.size() - NEXT_TO_TOP], cHull.getSet()[cHull.size() - TOP], p)
              != COUNTERCLOCKWISE)
        {
            cHull.removeLast();
        }

        cHull.add(p);
    }
}

/**
 * @brief Finds minimum Y point and its index
 * @param pSet PointSet to analyze
 * @param minY pointer to the variable where the minimum Y value will be stored
 * @param min pointer to the variable where the index of the point will be stored
 */
void getMin(const PointSet &pSet, int *minY, int *min)
{
    for (int i = NEXT_TO_PIVOT; i < pSet.size(); i++)
    {
        int y = pSet.getSet()[i].getY();

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < *minY) || (*minY == y && pSet.getSet()[i].getX() < pSet.getSet()[*min].getX()))
        {
            *minY = pSet.getSet()[i].getY();
            *min = i;
        }
    }
}

int main()
{
    Point p;
    PointSet convex, pSet;

    while (std::cin >> p)
    {
        if(p.getX()==-666)
            break;
        pSet.add(p);
    }

    // check if 2 or less points were received. If yes, sort them and print the set.
    if(pSet.size() <= 2)
    {
        pSet.sort(PIVOT_INDEX, pSet.size());
        printConvex(pSet);
        return EXIT_SUCCESS;
    }

    // sort the set of points according to their polar angle.
    int minY = pSet.getSet()[PIVOT_INDEX].getY(), min = 0;
    getMin(pSet, &minY, &min);

    swap(pSet.getSet()[PIVOT_INDEX], pSet.getSet()[min]);

    p0 = pSet.getSet()[PIVOT_INDEX];
    pSet.sort(NEXT_TO_PIVOT, pSet.size(), compare);

    // get the convex hull set of points.
    grahamScan(pSet, convex);

    // sort the convex hull set of points
    convex.sort(PIVOT_INDEX, convex.size());
    // print points in the convex hull.
    printConvex(convex);

    return EXIT_SUCCESS;
}

