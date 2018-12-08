#pragma once
#include "simulation.h"


//helper methods
Point cp(int x, int y, int z) { return Point(x, y, z);}
Vector cv(int x, int y, int z) {return Vector(x, y, z);}
Vector down_vector(){return cv(0, 0, -1);}

int simulation::draw_p(Point &p){return 1;}
int simulation::draw_ray(XRay &x) { return 1;}
//pseudo destructor
int simulation::clean_scene() { return 1; }

std::forward_list<Sphere> make_sample()
{
	Sphere sample1 = Sphere(0, 0, 0, SPHERE_RADIUS);
	std::forward_list<Sphere> ret = std::forward_list<Sphere>();
	ret.push_front(sample1);
	return ret;
}

float simulation::get_ior(XRay &p)
{
	Point f = p.get_src() + p.get_dir().traverse(.001f);
	float sqrmag = f.get_magnitude();
	if (sqrmag - SPHERE_RADIUS <= ZERO_MAX)
		return 1.1f;
	return 1.0f;
}

simulation::simulation()
{
	detector_plate = DetectorPlate(cp(-DETECTOR_PLATE_SIZE ,- DETECTOR_PLATE_SIZE, - DETECTOR_PLATE_DEPTH), cp(DETECTOR_PLATE_SIZE,-DETECTOR_PLATE_SIZE, - DETECTOR_PLATE_DEPTH), DETECTOR_PLATE_WIDTH, DETECTOR_PLATE_HEIGHT);
	
	sample = make_sample();
	camera = Raygun(cp(0, 0, CAMERA_SOURCE_DEPTH), down_vector(), FIELD_OF_VIEW_DEGREES, ASPECT_RATIO, DEFAULT_INDEX_OF_REFRACTION, INITIAL_INTENSITY, XRAY_COUNT_HORIZONTAL, XRAY_COUNT_VERTICAL);
	xray_list = camera.create_rays(0);
}

int simulation::run_scene()
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
			//this XRay is now completely processed, now draw and compute children
			draw_ray(*it_xlist);
			xray_list.push_front(it_xlist->reflect(colliding_object_norm));
			xray_list.push_front(it_xlist->refract(colliding_object_norm, get_ior(*it_xlist)));
		}
		//no collision, check for detector plate collision, 
		else
			detector_plate.test_ray(*it_xlist);
	}
	return 0;
}

