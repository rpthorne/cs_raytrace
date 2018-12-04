/****************************************************************
 *	Abstract Plane
 *
 *	An abstract class that discerns a plane within 3-dimensional
 * space. An abstract plane consists of 3 points, a vector, and a
 * a float. The constructor requires three points and calculates 
 * the (normalized) normal vector upon construction. There is a
 * getter for the normal vector, as well as a getter for the 
 * (constant) determinant.
 *
 ****************************************************************/

#pragma once
#include <math.h>
#include "Point.h"
#include "Vector.h"
#include "XRay.h"

class AbstractPlane
{
protected:
	//to move????? not good oop
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

	Vector get_normal() const;

	//math ops on planes

	//returns the amount by which p should be multiplied to the collision point
	//only returns values for which it collides with <| p
	virtual float ray_plane_collision(const XRay &p) const  = 0;

};
