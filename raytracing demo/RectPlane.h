#pragma once
#include "AbstractPlane.h"
class RectPlane :
	public AbstractPlane
{
public:
	RectPlane();
	~RectPlane();

	RectPlane(Pointf &a, Pointf &b, Pointf &c);
	float ray_plane_collision(XRay &p);
};

