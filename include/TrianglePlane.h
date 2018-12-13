/****************************************************************
 *	TrianglePlane
 *
 *	Triangle plane represents a 2-d triangle in 3-d space.
 * triangle defined with letters
 *
 * b
 * |\
 * | \
 * a--c
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include "AbstractPlane.h"
#include"Point.h"

class TrianglePlane : public AbstractPlane
{
public:
	TrianglePlane(const Point a, const Point b, const Point c);
	TrianglePlane(const Point a, const Vector b, const Vector c);
	float ray_plane_collision(const XRay &p)const;
};