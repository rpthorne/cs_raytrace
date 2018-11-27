/****************************************************************
 *	Point
 *
 *	Point class inherits the AbstractPoint class. It contains a
 * default constructor, standard constructor requiring 3 floats,
 * as well as some overriding operator methods: Binary + and - as
 * well as unary -.
 *
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
};

