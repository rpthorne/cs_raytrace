#include "XRay.h"
#include <math.h>

//constructors
XRay::XRay() {
	dir = Pointf();
	src = Pointf();
	intensity = 0;
}

XRay::XRay(Pointf sr, Pointf dest) {
	dir = dest;
	src = sr;
}

XRay XRay::refract_through(XRay& norm, float index_of_refraction_1, float index_of_refraction_2)
{
	//normalize this
	Pointf p = dir.scale_mul(sqrtf(dir.dot_product(dir)));
	Pointf result;
	float refract_index = index_of_refraction_1 / index_of_refraction_2;
	float vector_dot = p.dot_product(-norm.dir);
	result = p.scale_mul(refract_index) + norm.dir.scale_mul(refract_index * vector_dot - sqrt(1 - refract_index * refract_index * (1 - vector_dot * vector_dot)));
	return XRay(norm.src, result);
}

float XRay::magnitude_precise()
{
	return sqrtf(dir.dot_product(dir));
}

XRay XRay::scale_mul(const float mul) const
{
	XRay res;
	res.src = src;
	res.dir.x = this->x * mul;
	res.dir.y = this->y * mul;
	res.dir.z = this->z * mul;
	return res;
}