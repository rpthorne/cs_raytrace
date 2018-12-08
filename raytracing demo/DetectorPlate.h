/****************************************************************
 *	DetectorPlate
 *
 *	 a detector plate is designed to capture XRays that collide 
 * with it. any XRay that collides with a detector plate should be
 * captured by the detector plate, and cannot pass through, or 
 * reflect/refract. 
 * 
 *	 the detector plate has a resolution describing the discrete 
 * "pixels" that an XRay can hit on the detector. each pixel must
 * be capable of computing information based on all XRays that 
 * intersect that particular pixel, produceable as a deplentry
 *
 *	 Additionally, detector plates should be able to support an add
 * operation that allows the combining of two separate detector
 * plates that have the same definitions (specifically, height and
 * width, but also expectedly the same size and position). this 
 * feature is for parallelization of a single scene
 *
 * @author
 * Ryan Thorne
 * Nic Cox
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
	DetectorPlate();
	DetectorPlate(const Point &begin_, const Point &end_, int width_, int height_);

	//getters
	int collect_rays(deplentry***) const;

	//mutators
	int test_ray(XRay &p);
};