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
 * Nick Cox
 ****************************************************************/

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
	//assumes only one camera
	Raygun(const Point x_source_, const Vector c_source_,
		float fov_, float aspect_ratio_,
		float index_of_refraction_, float intensity_,
		int ray_width_, int ray_height_);
	//camera id refers to the one-dimensional value (tot_colls * col + row) of the desired camera
	std::forward_list<XRay> create_rays(int camera_id);
};