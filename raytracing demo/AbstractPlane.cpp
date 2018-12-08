/****************************************************************
 *	Abstract Plane
 *
 *	An abstract class that discerns a plane within 3-dimensional
 * space. An abstract plane consists of 3 points, and a vector,
 * representing the normal of the plane. The constructor requires
 * three points and calculates the (normalized) normal vector
 * upon construction.
 *
 *   since three points are sufficient and necessary for a plane
 * definition, the abstract plane only keeps track of that many
 * any derived classes can concern themselves with more points at
 * there leisure
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
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