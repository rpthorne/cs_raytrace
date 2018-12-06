/****************************************************************
 *	className
 *
 *	description of class
 *
 ****************************************************************/

#include "DetectorPlate.h"
#include "Sphere.h"
#include "Raygun.h"
#include <forward_list>

#ifndef ZERO_MAX
#define ZERO_MAX (0.0001f)
#endif // !ZERO_MAX


//detector plate size
#define DETECTOR_PLATE_SIZE (1)
//detector plate depth
#define DETECTOR_PLATE_DEPTH (2)
//detector plate width
#define DETECTOR_PLATE_WIDTH (5)
//detector plate height
#define DETECTOR_PLATE_HEIGHT (5)
//sphere radius
#define SPHERE_RADIUS (1)
//camera source depth
#define CAMERA_SOURCE_DEPTH (4)
//field of view in degrees?
#define FIELD_OF_VIEW_DEGREES (90.0f)
//aspect ratio
#define ASPECT_RATIO (1.0f)
//xray count horizontally
#define XRAY_COUNT_HORIZONTAL (2.0f)
//xray count vertically
#define XRAY_COUNT_VERTICAL (2.0f)
//initial index of refraction
#define DEFAULT_INDEX_OF_REFRACTION (1.0f)
//initial intensity
#define INITIAL_INTENSITY (1.0f)

std::forward_list<Sphere> sample;
Raygun camera;
std::forward_list<XRay> xray_list;
DetectorPlate detector_plate;

Point cp(int x, int y, int z)
{
	return Point(x, y, z);
}

Vector cv(int x, int y, int z)
{
	return Vector(x, y, z);
}

std::forward_list<Sphere> make_sample()
{
	Sphere sample1 = Sphere(0, 0, 0, SPHERE_RADIUS);
	std::forward_list<Sphere> ret = std::forward_list<Sphere>();
	ret.push_front(sample1);
	return ret;
}


Vector down_vector()
{
	return cv(0, 0, -1);
}

int draw_p(Point &p)
{
	return 0;
}


float get_ior(XRay &p)
{
	Point f = p.get_src() + p.get_dir().traverse(.001f);
	float sqrmag = f.getX() * f.getX() + f.getY() * f.getY() + f.getZ() * f.getZ();
	if (sqrmag - SPHERE_RADIUS <= ZERO_MAX)
		return 1.1f;
	return 1.0f;
}


int setup_scene()
{
	detector_plate = DetectorPlate(cp(-DETECTOR_PLATE_SIZE ,- DETECTOR_PLATE_SIZE, - DETECTOR_PLATE_DEPTH), cp(DETECTOR_PLATE_SIZE,-DETECTOR_PLATE_SIZE, - DETECTOR_PLATE_DEPTH), DETECTOR_PLATE_WIDTH, DETECTOR_PLATE_HEIGHT);
	
	sample = make_sample();
	camera = Raygun(cp(0, 0, CAMERA_SOURCE_DEPTH), down_vector(), FIELD_OF_VIEW_DEGREES, ASPECT_RATIO, DEFAULT_INDEX_OF_REFRACTION, INITIAL_INTENSITY, XRAY_COUNT_HORIZONTAL, XRAY_COUNT_VERTICAL);
	xray_list = camera.create_rays(0);
	return 0;
}

int run_scene()
{
	for (std::forward_list<XRay>::iterator it_xlist = xray_list.begin(); it_xlist != xray_list.end(); it_xlist++)
	{
		float length = -1;
		Vector colliding_object_norm;
		Point colliding_object_loc;
		//simple check all elements for now
		for (auto it_samplelist = sample.begin(); it_samplelist != sample.end(); it_samplelist++)
		{
			float res;
			Vector norm;
			Point loc;
			it_samplelist->collision(*it_xlist, res, loc, norm);
			if (res > 0 && res < length)
			{
				length = res;
				colliding_object_norm = norm;
				colliding_object_norm = loc;
			}
		}
		//if there was collision with sample, compute ray split, add new rays to end of list
		if (length > 0)
		{
			it_xlist->set_length(length);
			//blank atm duh
			xray_list.push_front(it_xlist->reflect(colliding_object_norm));
			xray_list.push_front(it_xlist->refract(colliding_object_norm, get_ior(*it_xlist)));
		}
		//no collision, check for detector plate collision, 
		else
			detector_plate.test_ray(*it_xlist);
	}
	return 0;
}


int clean_scene()
{
	//here we output data from simulation
	return 0;
}