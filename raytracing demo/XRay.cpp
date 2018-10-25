#include "XRay.h"
#include <math.h>

//constructors
XRay::XRay() {
	this->dir = Pointf();
	this->src = Pointf();
	this->intensity = 0;
	this->length = -1;
	this->reflect_count = 0;
}

XRay::XRay(Pointf src, Pointf dir, float intensity) {
	this->dir = dir;
	this->src = src;
	this->intensity = intensity;
	this->length = -1;
	this->reflect_count = 0;
}

XRay::XRay(Pointf src, Pointf dir, float intensity, int reflect_count) {
	this->dir = dir;
	this->src = src;
	this->intensity = intensity;
	this->length = -1;
	this->reflect_count = reflect_count;
}

Pointf XRay::refract_through(Pointf& norm, float index_of_refraction_1, float index_of_refraction_2)
{
	//normalize this
	Pointf p = dir.scale_mul(sqrtf(dir.dot_product(dir)));
	Pointf result;
	float refract_index = index_of_refraction_1 / index_of_refraction_2;
	float vector_dot = p.dot_product(-norm);
	result = p.scale_mul(refract_index) + norm.scale_mul(refract_index * vector_dot - sqrt(1 - refract_index * refract_index * (1 - vector_dot * vector_dot)));
	return result;
}

XRay XRay::scale_mul(const float mul) const
{
	XRay res;
	res.src = src;
	res.dir = dir.scale_mul(mul);
	return res;
}
