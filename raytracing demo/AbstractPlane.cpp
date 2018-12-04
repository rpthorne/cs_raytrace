/****************************************************************
 *	className
 *
 *	description of class
 *
 ****************************************************************/

#include "AbstractPlane.h"
#include "Point.h"
#include "Vector.h"

Vector AbstractPlane::get_normal() const
{
	return normal;
}


float AbstractPlane::get_determinant(const Point &a, const Point &b, const Point &c) const
{
	return a.getX() * b.getY() * c.getZ() + a.getZ() * b.getX() * c.getY() + a.getY() * b.getZ() * c.getX() - \
		a.getX() * b.getZ() * c.getY() - a.getY() * b.getX() * c.getZ() - a.getZ() * b.getY() * c.getX();
}