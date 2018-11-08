#pragma once
#include "XRay.h"
#include "Point.h"
#include <forward_list>

class Raygun
{
	Pointf x_source;
	Pointf c_source;
	float fov;
	float aspect_ratio;
public:
	Raygun();
	~Raygun();
	// standard constructor
	Raygun(const Pointf x_source_, const Pointf c_source_, float fov_, float aspect_rario_, int width_, int height_);
	std::forward_list<XRay> create_rays();
};