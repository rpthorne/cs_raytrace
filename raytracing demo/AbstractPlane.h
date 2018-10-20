#includes <math.h>

class AbstractPlane
{
protected:
	Pointf a,b,c;
	//stored for ease of computation
	Pointf normal;
public:
	AbstractPlane(Pointf a, Pointf b, Pointf c) {
		this->a = a;
		this->b = b;
		this->c = c;
		//compute normal now, so dont have to later
		Pointf p, q, r;
		p = b - a;
		q = c - a;
		//cross product, inlined
		r.x = (p.y * q.z) - (p.z * q.y);
		r.y = (p.z * q.x) - (p.x * q.z);
		r.z = (p.x * q.y) - (p.y * q.x);
		//normalize
		normal = r.scale_mul(sqrtf(r.dot_product(r)));
	}
	//returns the amount by which p should be multiplied to the collision point
	//only returns values for which it collides with <| p
	virtual float ray_plane_collision(XRay &p) = 0;
	Pointf normal() {return normal;};
}
