//
// Created by jenia on 04/09/2016.
//

#ifndef POINT_H
#define POINT_H
\
#include <sstream>

/**
 * @brief a class representing a point
 */
class Point
{
	int _x, _y;
	bool isInit;
public:
	Point();
	/**
	 * @brief Ctor
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	Point(int x, int y);

	/**
	 * Destructor
	 */
	~Point();

	/**
	 * @brief Sets the (x,y) coordinates of the point
	 * @param x the x coordinate
	 * @param y the y coordinate
	 */
	void set(int x, int y);

	inline int getX() const
	{
		return _x;
	}

	inline int getY() const
	{
		return _y;
	}

	Point& operator=(const Point& p);
	int compare(const Point& p);
	int compare(const Point& p1, const Point& p2);

	bool operator ==(const Point& p) const;
	bool operator<(Point p1);

	friend std::istream& operator>>(std::istream& is, Point& point);

	/**
	 * @brief Prints the point in a specialized format
	 */
	std::string toString();
};


#endif //POINT_H
