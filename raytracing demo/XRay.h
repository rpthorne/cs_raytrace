#pragma once
#include "Point.h"
#include "Vector.h"

//length assumed to be one
class XRay
{
	Pointf src;
	Pointf dir; //guaranteed to be normal
	float intensity;
	float length; // absolute length of this ray, not optical length of this ray
	int generation;
	float optical_pathlength;
	float current_index_of_refraction;

	//secret constructor for generational tracking
	XRay(Point const &src_, Vector const &dir_, float index_of_refraction_, float intensity_, short generation_);
public:
	//constructers

	XRay();
	XRay(Point const &src_, Vector const &dir_, float index_of_refraction_, float intensity_);

	//getters

	const Vector get_dir() const;
	const Point get_src() const;
	float get_intensity() const;
	float get_optic_pathlength() const;
	float get_length() const;
	
	//operations

	int XRay::set_length(const float dist);

	//relfect take some output from refract in order to save time
	XRay XRay::reflect(Vector const &norm, float intensity_refracted) const;
	XRay XRay::refract(Vector const &norm, const float index_of_refraction, bool s_polarized) const;
	//XRay XRay::reflect_s(Pointf const &norm, float intensity_refracted) const { return reflect(norm, intensity_refracted, 1); };
	XRay XRay::refract_s(Pointf const &norm, float index_of_refraction) const { return reflect(norm, index_of_refraction); };
	//XRay XRay::reflect_p(Pointf const &norm, float intensity_refracted) const { return reflect(norm, intensity_refracted, 1); };
	XRay XRay::refract_p(Pointf const &norm, float index_of_refraction) const { return reflect(norm, index_of_refraction); };
};
