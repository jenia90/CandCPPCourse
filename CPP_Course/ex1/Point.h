//
// Created by jenia on 04/09/2016.
//

#ifndef POINT_H
#define POINT_H

#define DELMITER ","

#include <sstream>

/**
 * @brief a class representing a point
 */
class Point
{
	int _x, _y;
	bool _isInit;
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

	int getX() const
	{
		return _x;
	}

	int getY() const
	{
		return _y;
	}

	bool isInit() const
	{
		return _isInit;
	}

	Point& operator=(const Point& p);
	//static int compare(const Point& p1, const Point& p2);

	bool operator ==(const Point& p) const;
	bool operator !=(const Point& p) const;
	Point& operator -(const Point& p);
	bool operator<(const Point& p) const;
	friend std::istream& operator>>(std::istream& is, Point& point);

	/**
	 * @brief Prints the point in a specialized format
	 */
	std::string toString();
};


#endif //POINT_H
