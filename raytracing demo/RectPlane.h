#pragma once
#include "AbstractPlane.h"
#include "Point.h"
class RectPlane :
	public AbstractPlane
{
public:
	RectPlane();
	~RectPlane();

	RectPlane(const Point &a, const Point &b, const Point &c);
	float ray_plane_collision(const XRay &p) const ;
};

