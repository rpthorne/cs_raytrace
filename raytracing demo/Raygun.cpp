/****************************************************************
 *	Raygun
 *
 *	A Raygun produces some amount of XRays
 *
 * with parallelization in mind, a raygun is desinged to be a
 * singleton instance: there should only ever be one raygun for a
 * scene.
 *
 * constructing a raygun needs: the source of the Xrays, the
 * the XRays will be shot in ( the center of the cameras direction).
 *
 * the field of view in degrees, and aspect ratio. these parameters
 * define how wide the Rays spread, as well as how rectangular the
 * camera appears. for reference, a widescreen TV would have an
 * aspect ratio of 9/16 = .5625. a square would be 1.0.
 *
 * the initial values for the XRays, intensity, and index of
 * refraction. note that all XRays start with wave_directions in
 * the positive x-direction.
 *
 * ray_width and ray_height indicating the total number of rays in
 * both directions for a total of (ray_width * ray_height) XRays
 *
 * (optional) camera_width/height which indicate the number of
 * discrete cameras (camera_width * camera_height total) that
 * can be made from the raygun. a camera is a collection of rays
 * that are bundled together, and can be thought of as a sub-raygun.
 *
 * #--*--#
 * |4r|4r|
 * *--*--*
 * |4r|4r|
 * #--*--#
 *
 * ex. a 4w/4h rays and 2w/2h cameras would be able to analyze 16 rays
 * but each call to create_rays would only give 4 rays belonging to one
 * camera.
 *	note: the purpose of this is to analyze multiple sets of XRays in
 * parallel.
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include "Raygun.h"

Raygun::Raygun()
{
}


Raygun::~Raygun()
{
}


// standard constructor
Raygun::Raygun(const Point x_source_, const Vector c_source_,
	float fov_, float aspect_ratio_,
	float index_of_refraction_, float intensity_,
	int ray_width_, int ray_height_) 
{	Raygun(x_source_, c_source_, fov_, aspect_ratio_, index_of_refraction_, intensity_, ray_width_, ray_height_, 1, 1); }

Raygun::Raygun(const Point &x_source_, const Vector &c_source_,
	float fov_, float aspect_ratio_,
	float index_of_refraction_, float intensity_,
	int ray_width_, int ray_height_, int camera_width_, int camera_height_)
{
	
	x_source = x_source_;
	ray_width = ray_width_;
	ray_height = ray_height_;
	camera_width = camera_width_;
	camera_height = camera_height_;
	intensity = intensity_;
	index_of_refraction = index_of_refraction_;
	//convert fov_ to radians
	float fov_rad = fov_ * 3.14f / 180.0f;
	float nhalf = atanf(fov_rad * .5f);
	c_source = c_source_.traverse(1) - Point(nhalf * aspect_ratio_, nhalf , 0);
	w_dist = nhalf / ray_width;
	h_dist = nhalf * aspect_ratio_ / ray_height;
	ray_per_camera_h = ray_height / camera_width;
	ray_per_camera_w = ray_width / camera_height;
}


std::list<XRay> Raygun::create_rays(int camera_id) {
	std::list<XRay> ret = std::list<XRay>();
	//int xloc = camera_id % camera_width;
	//int yloc = camera_id / camera_width;
	for (int xloc = (camera_id % camera_width) * ray_per_camera_w * 2; xloc < ray_width * 2 && xloc < 2 * ray_per_camera_w * (camera_id % camera_width + 1); xloc += 2)
		for (int yloc = (camera_id / camera_width) * ray_per_camera_h * 2; yloc < ray_height * 2 && yloc < 2 * ray_per_camera_h * (camera_id / camera_height + 1); yloc += 2)
			ret.push_front(XRay(x_source, Vector(c_source + Vector(1, 0, 0).traverse((1 + xloc) * w_dist) + Vector(0, 1, 0).traverse((1 + yloc) * h_dist)), Vector(1,0,0), index_of_refraction, intensity));
	return ret;
}