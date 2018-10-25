#include "TrianglePlane.h"
#include "AbstractPlane.h"
#include "pointf.h"
#include "XRay.h"


TrianglePlane::TrianglePlane(Pointf a, Pointf b, Pointf c) : AbstractPlane(a, b, c) {};

float TrianglePlane::ray_plane_collision(XRay &p)
{
	//Pointf t0 = b - a;
	//Pointf t1 = c - a;
	//Pointf t2 = p.scale_mul(-1);
	//write this
	return 0.0f;
}
