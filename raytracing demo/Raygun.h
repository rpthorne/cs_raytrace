#pragma once
#include "XRay.h"
#include "Point.h"
#include <forward_list>

class Raygun
{
	Point x_source;
	Point c_source;
	float fov;
	float aspect_ratio;
public:
	Raygun();
	~Raygun();
	// standard constructor
	Raygun(const Point x_source_, const Point c_source_, float fov_, float aspect_rario_, int width_, int height_);
	std::forward_list<XRay> create_rays();
};