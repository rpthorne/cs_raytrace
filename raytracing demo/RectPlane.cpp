#include "RectPlane.h"



RectPlane::RectPlane() : AbstractPlane(Pointf(), Pointf(), Pointf())
{
}

RectPlane::RectPlane(Pointf &a, Pointf &b, Pointf &c) : AbstractPlane(a, b, c)
{
}

float RectPlane::ray_plane_collision(XRay &p)
{
	return 0;
}


RectPlane::~RectPlane()
{
}
