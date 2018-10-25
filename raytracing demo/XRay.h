#pragma once
#include "Pointf.h"

//length assumed to be one
class XRay
{
private:
	Pointf src;
	Pointf dir;
	float intensity;
	float length;
	int reflect_count;
public:
	Pointf XRay::refract_through(Pointf& norm, float index_of_refraction_1, float index_of_refraction_2);
	XRay();
	XRay(Pointf, Pointf, float intensity);
	XRay(Pointf, Pointf, float, int);
	XRay XRay::scale_mul(const float mul) const;
	float XRay::get_length() { return length; };
};
