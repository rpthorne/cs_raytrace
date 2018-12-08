/****************************************************************
 *	className
 *
 *	description of class
 *
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
	: Raygun(x_source_, c_source_, fov_, aspect_ratio_, index_of_refraction_, intensity_, ray_width_, ray_height_, 1, 1) {}

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
	float nhalf = atanhf(fov_ * .5f);
	c_source = c_source_.traverse(1) - Point(nhalf * aspect_ratio_, nhalf , 0);
	w_dist = nhalf / ray_width;
	h_dist = nhalf * aspect_ratio_ / ray_height;
	ray_per_camera_h = camera_height / ray_height;
	ray_per_camera_w = camera_width / ray_width;
}


std::forward_list<XRay> Raygun::create_rays(int camera_id) {
	std::forward_list<XRay> ret = std::forward_list<XRay>();
	//int xloc = camera_id % camera_width;
	//int yloc = camera_id / camera_width;
	for (int xloc = (camera_id % camera_width) * ray_per_camera_w * 2; xloc < ray_width * 2 && xloc < 2 * ray_per_camera_w * (camera_width + 1); xloc += 2)
		for (int yloc = (camera_id / camera_width) * ray_per_camera_h * 2; yloc < ray_height * 2 && yloc < 2 * ray_per_camera_h * (camera_height + 1); yloc += 2)
			ret.push_front(XRay(x_source, Vector(c_source + Vector(1, 0, 0).traverse((1 + xloc) * w_dist) + Vector(0, 1, 0).traverse((1 + yloc) * h_dist)), Vector(1,0,0), index_of_refraction, intensity));
	return ret;
}