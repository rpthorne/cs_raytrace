#pragma once
#include "AbstractPlane.h"

class TrianglePlane : public AbstractPlane
{
public:
	TrianglePlane(const Pointf a, const Pointf b, const Pointf c);
	float ray_plane_collision(const XRay &p)const;
};