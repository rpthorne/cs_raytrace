/****************************************************************
* Point is a class representing a single point in 3-dimensional
* space 
*****************************************************************/


#pragma once
#include "AbstractPoint.h"
#include "Vector.h"
class Point :
	public AbstractPoint
{
public:

	Point();
	Point(const float x, const float y, const float z);
	
};

Point Point::operator- (Point &c) const;
Point Point::operator- () const;
Point Point::operator- (Point &c)const;
Point Point::operator+ (Point &c) const;
Vector Point::pointToVector() const;
