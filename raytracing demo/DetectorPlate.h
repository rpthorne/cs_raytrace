#pragma once
#include <forward_list>
#include "XRay.h"
#include "RectPlane.h"

class DetectorPlate
{
	std::forward_list<XRay>** buckets;
	RectPlane** b_coords;
	RectPlane detector_plane;
	Pointf x_vector;
	Pointf y_vector;
	Pointf begin;
	Pointf end;
	int width, height;

	//helper functions
	int DetectorPlate::add_to_bucket(const XRay &p, int x, int y);

public:

	//constructors
	DetectorPlate(const Pointf &begin_, const Pointf &end_, const Pointf &direction, int width_, int height_);

	//getters
	int collect_rays(std::forward_list<XRay>**) const;

	//mutators
	int test_ray(XRay &p);
};