#pragma once
#include <math.h>
#include "Pointf.h"
#include "XRay.h"

class AbstractPlane
{
protected:
	//to move????? not good oop
	float get_determinant(const Pointf&, const Pointf&, const Pointf&) const;

	//these represent three points that define the plane in 3d space
	Pointf a, b, c;
	//stored for ease of computation
	Pointf normal;
public:
	AbstractPlane(const Pointf &a, const Pointf &b, const Pointf &c) {
		this->a = a;
		this->b = b;
		this->c = c;
		//compute normal now, so dont have to later
		normal = (b - a).cross_product(c - a);
		//normalize
		normal = normal.normalize();
	}

	//getters

	Pointf get_normal() const;

	//math ops on planes

	//returns the amount by which p should be multiplied to the collision point
	//only returns values for which it collides with <| p
	virtual float ray_plane_collision(const XRay &p) const  = 0;

};
