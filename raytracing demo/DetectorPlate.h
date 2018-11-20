#pragma once
#include <forward_list>
#include "XRay.h"
#include "RectPlane.h"
#include "Point.h"
#include "Vector.h"

class DetectorPlate
{
	std::forward_list<XRay>** buckets;
	RectPlane** b_coords;
	RectPlane detector_plane;
	float x_vector;
	float y_vector;
	Point begin;
	Point end;
	int width, height;

	//helper functions
	int DetectorPlate::add_to_bucket(const XRay &p, int x, int y);

public:

	//constructors
	DetectorPlate(const Point &begin_, const Point &end_, int width_, int height_);

	//getters
	int collect_rays(std::forward_list<XRay>**) const;

	//mutators
	int test_ray(XRay &p);
};