#include "RectPlane.h"
#include "Point.h"

RectPlane::RectPlane() : AbstractPlane(Point(), Point(), Point())
{
}

RectPlane::RectPlane(const Point &a, const Point &b, const Point &c) : AbstractPlane(a, b, c)
{
}

float RectPlane::ray_plane_collision(const XRay &p) const
{
	Point t0 = b - a;
	Point t1 = c - a;
	Point t2 = -p.get_dir();
	Point t3 = p.get_src() - a;

	float det0 = get_determinant(t0, t1, t2);

	//free variable(s), cannot identify single solution
	if (fabsf(det0) < ZERO_MAX) return -1;

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
