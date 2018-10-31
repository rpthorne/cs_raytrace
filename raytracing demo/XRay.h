#pragma once
#include "Pointf.h"

//length assumed to be one
class XRay
{
	Pointf src;
	Pointf dir; //guaranteed to be normal
	float intensity;
	float length; // absolute length of this ray, not optical length of this ray
	int generation;
	float optical_distance;
	float current_index_of_refraction;

	//secret constructor for generational tracking
	XRay(Pointf const &src_, Pointf const &dir_, const float index_of_refraction_, float const intensity_, int const generation_);

public:
	//constructers

	XRay();
	XRay(Pointf const &src_, Pointf const &dir_, const float index_of_refraction_, float const &intensity_);

	//getters

	const Pointf get_dir() const;
	const Pointf get_src() const;
	float get_intensity() const;
	float get_optic_path_length() const;
	float get_length() const;
	
	//operations

	int XRay::set_length(const float dist);
	XRay XRay::reflect(Pointf const &norm, const int total_internal) const;
	XRay XRay::refract(Pointf const &norm, const float index_of_refraction) const;
};
