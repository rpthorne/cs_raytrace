#include "AbstractPlane.h"
#include "pointf.h"
#include "XRay.h"

class TranglePlane : AbstractPlane
{
	float ray_plane_collision(XRay &p)
	{
		Pointf t0 = b - a;
		Pointf t1 = c - a;
		Pointf t2 = -p;
			return 0.0f;
	}
};
