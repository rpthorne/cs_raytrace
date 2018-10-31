#include "RectPlane.h"



RectPlane::RectPlane() : AbstractPlane(Pointf(), Pointf(), Pointf())
{
}

RectPlane::RectPlane(const Pointf &a, const Pointf &b, const Pointf &c) : AbstractPlane(a, b, c)
{
}

float RectPlane::ray_plane_collision(const XRay &p) const
{
	Pointf t0 = b - a;
	Pointf t1 = c - a;
	Pointf t2 = -p.get_dir();
	Pointf t3 = p.get_src() - a;

	float det0 = get_determinant(t0, t1, t2);

	//free variable(s), cannot identify single solution
	if (abs(det0) < ZERO_MAX) return -1;

	float detr3 = det0 / get_determinant(t0, t1, t3);// length of ray to return;
	if (detr3 < 0) return -1;

	float detr1 = det0 / get_determinant(t3, t1, t2);
	if (detr1 < 0) return -1;

	float detr2 = det0 / get_determinant(t0, t3, t2);
	if (detr2 < 0) return -1;

	if (detr2 > 1 || detr1 > 1) return -1;

	return detr3;
}


RectPlane::~RectPlane()
{
}
