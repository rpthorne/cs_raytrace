#include "Pointf.h"
#include <math.h>


class Pointf
{
public:
	float x, y, z;
	Pointf Pointf::operator- (const Pointf& c) const
	{
		Pointf res;
		res.x = this->x - c.x;
		res.y = this->y - c.y;
		res.z = this->z - c.z;
		return res;
	}

	Pointf Pointf::operator+ (const Pointf& c) const
	{
		Pointf res;
		res.x = this->x + c.x;
		res.y = this->y + c.y;
		res.z = this->z + c.z;
		return res;
	}
	//performs dot product like * should on vectors
	float Pointf::dot_product(const Pointf& c) const { return this->x * c.x + this->y * c.y + this->z * c.z; }

	Pointf Pointf::scale_div(const float div) const
	{
		Pointf res;
		res.x = this->x / div;
		res.y = this->y / div;
		res.z = this->z / div;
		return res;
	}
	Pointf Pointf::scale_mul(const float mul) const
	{
		Pointf res;
		res.x = this->x * mul;
		res.y = this->y * mul;
		res.z = this->z * mul;
		return res;
	}

	//doesnt work, dont use
	PointfA Pointf::asArray()
	{
		PointfA f = { this->x, this-> y, this->z };
		return f;
	}

	//slow and very accurate calculation
	float Pointf::magnitude_precise()
	{
		return sqrtf(this->dot_product(*this));
	}

	Pointf Pointf::reflect_across(Pointf norm) const
	{
		Pointf res;
		res.x = this->x;
		res.y = this->y;
		res.z = this->z;
		res = res - (norm.scale_mul(2.0f * this->dot_product(norm)));
		return res;
	}

	Pointf surf_norm(Pointf base, Pointf v1, Pointf v2)
	{
		Pointf p, q, r;
		p.x = v1.x - base.x;
		p.y = v1.y - base.y;
		p.z = v1.z - base.z;
		q.x = v2.x - base.x;
		q.y = v2.y - base.y;
		q.z = v2.z - base.z;
		r.x = (p.y * q.z) - (p.z * q.y);
		r.y = (p.z * q.x) - (p.x * q.z);
		r.z = (p.x * q.y) - (p.y * q.x);
		//p.x will be sacrificed to save our norms, dont let it go to waste!
		p.x = sqrtf(r.dot_product(r));
		r.x *= p.x;
		r.y *= p.x;
		r.z *= p.x;
		return r;
	}
};