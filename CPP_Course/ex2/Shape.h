/**
 * @file Shape.h
 * @author jenia90
 * @version 1.0
 * @date 15 Sep 2016
 *
 * @brief Header file containg the declarations of the Shape class and its members
 * @section DESCRIPTION:
 * Abstract class of a shape. It support such actions as checking for intersects of 2 shapes,
 * initializing the shape's edges and holds the shape factory static method.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "PrintOuts.h"
#include <memory>
#include "Defs.h"
#include "Point.h"
#include "Line.h"

#define COLLINEAR 0
#define CLOCKWISE 1
#define COUNTERCLOCKWISE 2

#define TYPE_CHAR_ERROR "Wrong type character passed!"

class Shape {

    /**
     * @brief given a vector container of Points returns a vector container of Lines created by
     * these points.
     * @param vertices vector container of Point objects
     * @return vector container of Line objects
     */
    std::vector<Line> initEdges(std::vector<Point> &vertices);

    /**
     * @brief helper method to check for intersection of shapes using point orientation,
     * @param shp Shape object reference
     * @return true if shapes intersect; false otherwise.
     */
    bool pointIntersect(const Shape& shp);

    /**
     * @brief helper method to check for intersection of shapes by checking if their edges intersect
     * @param shp Shape object reference
     * @return true if shapes intersect; false otherwise.
     */
    bool lineIntersect(const Shape& shp);
public:


    std::vector<Point> _vertices;
	std::vector<Line> _edges;

    /**
     * @brief ctor. given an array of Point objects inits the shape
     * @param points Point object vector container
     */
    Shape(std::vector<Point> &points);
    /**
     * dtor
     */
    ~Shape();

    void deleteShape();

    /**
     * @brief Gets the orientation of 3 points in respect to each other
     * @param a Point object
     * @param b Point object
     * @param c Point object
     * @return 0 if collinear; 1 if clockwise; 2 if counterclockwise
     */
	int orientation(Point a, Point b, Point c);

    /**
     * @brief A function used to validate a set of points and check if it's valid for a given shape
     * @param points Point object vector
     * @return true if valid; false otherwise.
     */
    virtual bool validateShape(std::vector<Point> &points) = 0;

    /**
     * Pure virtual method to calculate the area of a Shape.
     */
    virtual CordType calculateArea() = 0;

    /**
     * Pure virtual method which prints the shape
     */
    virtual void printShape() = 0;

    /**
     * Pure virtual method, if error occured, prints the error to std::cerr and exists with
     * EXIT_FAILURE code
     */
    virtual void exitWithError() = 0;

    /**
     * @brief Getter for the shape vertices
     * @return vector container of Point objects
     */
	std::vector<Point> getPoints() const
	{
		return _vertices;
	}

    /**
     * @brief Getter for the shape edges.
     * @return vector container of Line objects
     */
    std::vector<Line> getEdges() const
    {
        return _edges;
    }

    /**
     * @brief Overload of & operator to check for shape intersect
     * @param shp second Shape object reference
     * @return true if shapes intersect; false otherwise
     */
    bool operator&(const Shape& shp);

    /**
     * @brief Shape object factory method. Given a type char and array of points returns a new
     * shape of given type.
     * @param type type of the shape
     * @param points vector container of Point objects which create the shape
     * @return Shape object pointer.
     */
    static std::shared_ptr<Shape> createShape(char type, std::vector<Point> &points);
};


#endif //SHAPE_H
