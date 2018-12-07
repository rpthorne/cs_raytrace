/****************************************************************
 *	Point
 *
 *	Point class inherits the AbstractPoint class. It contains a
 * default constructor, standard constructor requiring 3 floats,
 * as well as some overriding operator methods: Binary + and - as
 * well as unary -. Also contains a method to return the magnitude
 * of the point as if it were a non-normalized vector.
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

