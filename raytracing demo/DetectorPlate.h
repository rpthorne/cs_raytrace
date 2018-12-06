/****************************************************************
 *	className
 *
 *	description of class
 *
 ****************************************************************/

#pragma once
#include <forward_list>
#include "XRay.h"
#include "RectPlane.h"
#include "Point.h"
#include "Vector.h"

struct deplentry
{
	float complex_intensity;
	Vector intensity_dir;
	float simple_intensity;
	int num_hits;
};

class DetectorPlate
{
	std::forward_list<XRay>** buckets;
	RectPlane** bucket_coords;
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
	int collect_rays(deplentry***) const;

	//mutators
	int test_ray(XRay &p);
};