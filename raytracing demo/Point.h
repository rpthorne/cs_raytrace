/****************************************************************
 *	Point
 *
 *	Point class inherits the AbstractPoint class. It is a class
 * defining a point in 3-dimensional space, composed of 3 float
 * values: one for the x, y, and z components
 *
 * @author
 * Ryan Thorne
 * Nick Cox
 ****************************************************************/

#pragma once
#include "AbstractPoint.h"

class Point :
	public AbstractPoint
{
public:
	Point();
	Point(const float x, const float y, const float z);
	
	Point Point::operator- () const;
	Point Point::operator- (Point const &c)const;
	Point Point::operator+ (Point const &c) const;
	float Point::get_magnitude();
};

