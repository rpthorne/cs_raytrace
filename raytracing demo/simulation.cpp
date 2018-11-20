
#include "DetectorPlate.h"
#include "Sphere.h"
#include "Raygun.h"
#include <forward_list>


//detector plate size
#define dps (1)
//detector plate depth
#define dpd (2)
//detector plate width
#define dpw (5)
//detector plate height
#define dph (5)
//sphere radius
#define spr (1)
//camera source depth
#define cams (4)
//field of view in degrees?
#define fov (90.0f)
//aspect ratio
#define aspr (1.0f)
//xray count horizontally
#define xrw (2.0f)
//xray count vertically
#define xrh (2.0f)
//initial index of refraction
#define iori (1.0f)
//initial intensity
#define intii (1.0f)

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
	Sphere sample1 = Sphere(0, 0, 0, spr);
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


int setup_scene()
{
	detector_plate = DetectorPlate(cp(-dps ,- dps, - dpd), cp(dps,-dps, - dpd), dpw, dph);
	
	sample = make_sample();
	camera = Raygun(cp(0, 0, cams), down_vector(), fov, aspr, iori, intii, xrw, xrh);
	xray_list = camera.create_rays(0);
	
}

int run_scene()
{
	for (auto it_xlist = xray_list.begin(); it_xlist != xray_list.end(); it_xlist++)
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
				//also store a pointer to our colliding sample maybe a &* is wrong, look into this maybe?
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
			xray_list.push_front(it_xlist->refract(colliding_object_norm, get_ior(colliding_object_loc)));
		}
		//no collision, check for detector plate collision, 
		else
			detector_plate.test_ray(*it_xlist);
	}
	return 0;
}

float get_ior(Point const &p)
{
	float sqrmag = p.getX() * p.getX() + p.getY() * p.getY() + p.getZ() * p.getZ();
	if (sqrmag <= spr + .0001f)
		return 1.1f;
	return 1.0f;
}


int clean_scene()
{
	//here we output data from simulation
	return 0;
}