#pragma once
#include "XRay.h"
#include "Point.h"
#include "Vector.h"
#include <forward_list>

class Raygun
{
	Point x_source;
	Point c_source;
	int ray_width;
	int ray_height;
	int camera_width;
	int camera_height;
	float w_dist;
	float h_dist;
	int ray_per_camera_h;
	int ray_per_camera_w;
	float intensity;
	float index_of_refraction;
public:
	Raygun();
	~Raygun();
	// standard constructor
	Raygun(const Point &x_source_, const Vector &c_source_, 
		float fov_, float aspect_ratio_, 
		float index_of_refraction_, float intensity_, 
		int ray_width_, int ray_height_, int camera_width_, int camera_height_);
	Raygun(const Point x_source_, const Vector c_source_,
		float fov_, float aspect_ratio_,
		float index_of_refraction_, float intensity_,
		int ray_width_, int ray_height_);
	std::forward_list<XRay> create_rays(int camera_id);
};