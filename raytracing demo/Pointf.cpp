#include "Pointf.h"
#include <math.h>


//from "Quake III Arena"
//https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
//(lines 552 - 572) taken from wikepedia article, unmodified:
//https://en.wikipedia.org/wiki/Fast_inverse_square_root#cite_note-quakesrc-6
//finds the approximate inverse square root in a short, time efficient manner.
float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
										   // y = y * (threehalfs - (x2 * y * y));   // 2nd iteration, this can be removed

	return y;
}


Pointf::Pointf() { x = 0; y = 0; z = 0; }
Pointf::Pointf(float a, float b, float c) { this->x = a; this->y = b; this->z = c; }
float Pointf::getX() const {return x;}
float Pointf::getY() const { return y; }
float Pointf::getZ() const { return z; }
Pointf Pointf::operator- (const Pointf& c) const
{
	Pointf res;
	res.x = this->x - c.x;
	res.y = this->y - c.y;
	res.z = this->z - c.z;
	return res;
}


Pointf Pointf::operator- ()const
{
	Pointf res = { -x,-y,-z };
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

	
//slow and very accurate calculation
float Pointf::magnitude_precise() const
{
	return sqrtf(this->dot_product(*this));
}

Pointf Pointf::reflect_across(Pointf& norm) const
{
	Pointf res;
	res.x = this->x;
	res.y = this->y;
	res.z = this->z;
	res = res - (norm.scale_mul(2.0f * this->dot_product(norm)));
	return res;
}

Pointf Pointf::cross_product(Pointf &p) const
{
	return Pointf(this->y * p.z - this->z * p.y, this->z * p.x - this->x * p.z, this->x * p.y - this->y * p.x);
}

//assumes norm is, well, normal
//returns a normalized vector corresponding to the refracted direction
Pointf Pointf::refract_through(Pointf& norm, float index_of_refraction_1, float index_of_refraction_2)
{
	//normalize this
	Pointf p = normalize();
	Pointf result;
	float refract_index = index_of_refraction_1 / index_of_refraction_2;
	float vector_dot = p.dot_product(-norm);
	result = p.scale_mul(refract_index) + norm.scale_mul(refract_index * vector_dot - sqrt(1 - refract_index * refract_index * (1 - vector_dot * vector_dot)));
	return result;
}
	
//generates a surface normal out of the implied base and the two points specified
Pointf Pointf::surf_norm(const Pointf& v1, const Pointf& v2) const
{
	Pointf p, q, r;
	p = v1 - (*this);
	q = v2 - (*this);
	r.x = (p.y * q.z) - (p.z * q.y);
	r.y = (p.z * q.x) - (p.x * q.z);
	r.z = (p.x * q.y) - (p.y * q.x);
	r = r.scale_mul(Q_rsqrt(r.dot_product(r)));
	return r;
}

Pointf Pointf::normalize() const
{
	return scale_div(magnitude_precise());
}