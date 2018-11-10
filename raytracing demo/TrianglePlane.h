#pragma once
#include "AbstractPlane.h"
#include"Point.h"

class TrianglePlane : public AbstractPlane
{
public:
	TrianglePlane(const Point a, const Point b, const Point c);
	float ray_plane_collision(const XRay &p)const;
};