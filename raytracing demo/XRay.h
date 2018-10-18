#pragma once
#include "Pointf.h"


class XRay
{
private:
	Pointf src;
	Pointf dir;
	float intensity;
public:
	XRay XRay::refract_through(XRay& norm, float index_of_refraction_1, float index_of_refraction_2);
	XRay();
	XRay(Pointf, Pointf);
	XRay XRay::scale_mul(const float mul) const;
	float XRay::magnitude_precise();
};