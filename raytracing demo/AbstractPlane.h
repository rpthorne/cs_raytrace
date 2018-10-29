#pragma once
#include <math.h>
#include "Pointf.h"
#include "XRay.h"

class AbstractPlane
{
public:
	AbstractPlane(Pointf a, Pointf b, Pointf c) {
		this->a = a;
		this->b = b;
		this->c = c;
		//compute normal now, so dont have to latre
		normal = (b - a).cross_product(c - a);
		//normalize
		normal = normal.scale_mul(1.0f / sqrtf(normal.dot_product(normal)));
	}
	//returns the amount by which p should be multiplied to the collision point
	//only returns values for which it collides with <| p
	virtual float ray_plane_collision(XRay &p) = 0;
	Pointf get_normal();
protected:
	float get_determinant(Pointf, Pointf, Pointf);
	Pointf a, b, c;
	//stored for ease of computation
	Pointf normal;
};
