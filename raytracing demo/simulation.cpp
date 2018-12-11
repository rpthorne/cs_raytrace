/****************************************************************
*	simulation
*
*	simulation is the primary driver interface.
* simulation keeps track of the scene: which is made of
* 1:gunbox, 1:sample, 1:detectorplate, and many:XRays.
* when making some main, it is a good idea to derive it from simulation.
*
 * @author
 * Ryan Thorne
 * Nic Cox
****************************************************************/

#pragma once
#include "simulation.h"


//helper methods
Point cp(int x, int y, int z) { return Point(x, y, z);}
Vector cv(int x, int y, int z) {return Vector(x, y, z);}
Vector down_vector(){return cv(0, 0, -1);}

int simulation::draw_p(Point &p){return 1;}
int simulation::draw_ray(XRay &x) { return 1;}
//pseudo destructor
int simulation::clean_scene(deplentry **results) 
{ 
	detector_plate.collect_rays(results);
	//get intermediate results of simulation

	return 0; 
}

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
	detector_plate = DetectorPlate(cp(-DETECTOR_PLATE_SIZE * .5f ,- DETECTOR_PLATE_SIZE* .5f, - DETECTOR_PLATE_DEPTH), cp(DETECTOR_PLATE_SIZE * .5f, DETECTOR_PLATE_SIZE * .5f, - DETECTOR_PLATE_DEPTH), DETECTOR_PLATE_WIDTH, DETECTOR_PLATE_HEIGHT);
	
	sample = make_sample();
	camera = Raygun(cp(0, 0, CAMERA_SOURCE_DEPTH), down_vector(), FIELD_OF_VIEW_DEGREES, ASPECT_RATIO, DEFAULT_INDEX_OF_REFRACTION, INITIAL_INTENSITY, XRAY_COUNT_HORIZONTAL, XRAY_COUNT_VERTICAL);
	xray_list = std::queue<XRay, std::list<XRay>> (camera.create_rays(0));
}

int simulation::run_scene()
{
	while(!xray_list.empty())
	{
		XRay *it_x = &xray_list.front();
		float length = -1;
		Vector colliding_object_norm;
		Point colliding_object_loc;
		//simple check all elements for now
		for (auto it_samplelist = sample.begin(); it_samplelist != sample.end(); it_samplelist++)
		{
			float res;
			Vector norm;
			Point loc;
			it_samplelist->collision(*it_x, res, loc, norm);
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
			it_x->set_length(length);
			//this XRay is now completely processed, now draw and compute children
			draw_ray(*it_x);

			//calculate children
			XRay refl, refr;
			int err = it_x->collide(&refl, &refr, colliding_object_norm, get_ior(*it_x));
			//check error codes for reflected ray
			if (!(err & 1))
			{
				//put reflected ray onto queue
				xray_list.push(refl);
			}
			//check for refracted ray
			if (err < 2)
			{
				//put refracted ray onto queue
				xray_list.push(refr);
			}
		}
		//no collision, check for detector plate collision, 
		else
		{
			if (!detector_plate.test_ray(*it_x))
				draw_ray(*it_x);
		}
		xray_list.pop();
	}
	return 0;
}

