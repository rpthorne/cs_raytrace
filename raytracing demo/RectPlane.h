/****************************************************************
 *	RectPlane
 *
 *	A Rect Plane represents a 2-dimensional square in 3-dimensional
 * space.
 *
 * @author
 * Ryan Thorne
 * Nick Cox
 ****************************************************************/

#pragma once
#include "AbstractPlane.h"
#include "Point.h"

class RectPlane :
	public AbstractPlane
{
public:
	RectPlane();
	~RectPlane();

	/*points for constructor are marked with their variable
	*   b-----*
	*   |     |
	*   |     |
	*   a-----c
	*/
	RectPlane(const Point &a, const Point &b, const Point &c);
	float ray_plane_collision(const XRay &p) const ;
};

