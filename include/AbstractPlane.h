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
#include <math.h>
#include "Point.h"
#include "Vector.h"
#include "XRay.h"

class AbstractPlane
{
protected:
	//helper method for computing collision with arbitrary plane
	float get_determinant(const Point&, const Point&, const Point&) const;

	//these represent three points that define the plane in 3d space
	Point a, b, c;
	//stored for ease of computation
	Vector normal;
public:
	AbstractPlane(const Point &a, const Point &b, const Point &c) {
		this->a = a;
		this->b = b;
		this->c = c;
		//compute normal now, so dont have to later
		normal = (Vector(b - a)).cross_product(Vector(c - a));
	}

	//getters

	//same value for any point on plane
	Vector get_normal() const;


	//returns the amount by which p should be multiplied to the collision point
	//only returns values for which it collides with <| p
	virtual float ray_plane_collision(const XRay &p) const  = 0;

};
