#pragma once
#include "AbstractPlane.h"
class RectPlane :
	public AbstractPlane
{
public:
	RectPlane();
	~RectPlane();

	RectPlane(const Pointf &a, const Pointf &b, const Pointf &c);
	float ray_plane_collision(const XRay &p) const ;
};

