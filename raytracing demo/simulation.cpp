
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
#define fov (90)
//aspect ratio
#define aspr (1.0f)
//xray count horizontally
#define xrw (2)
//xray count vertically
#define xrh (2)




int setup_scene()
{
	DetectorPlate detector_plate = DetectorPlate(cp(-dps ,- dpd, - dps), cp(dps,-dpd,dps), cv(0,1,0), dpw, dph);
	
	std::forward_list<AbstractPlane> sample = make_sample();
	Raygun camera = Raygun(cp(0, 0, cams), down_vector(), fov, aspr, xrw, xrh);
	std::forward_list<XRay> xray_list = camera.create_rays();
	for (auto it_xlist = xray_list.begin(); it_xlist != xray_list.end(); it_xlist++)
	{
		float length = -1;
		AbstractPlane* colliding_object;
		//simple check all elements for now
		for (auto it_samplelist = sample.begin(); it_samplelist != sample.end(); it_samplelist++)
		{
			float res = it_samplelist->ray_plane_collision(*it_xlist);
			if (res > 0 && res < length)
			{
				length = res;
				//aslo store a pointer to our colliding sample maybe a &* is wrong, look into this maybe?
				colliding_object = &*it_samplelist;
			}
		}
		//if there was collision with sample, compute ray split, add new rays to end of list
		if (length > 0)
		{
			it_xlist->set_length(length);
			xray_list. it_xlist->refract(colliding_object->get_normal(), it_xlist->get_gen());/*need a good way to determine what sample i am in!!!!!!!*/

		}
		//no collision, check for detector plate collision, 
		else
			detector_plate.test_ray(*it_xlist);
	}
	return 0;
}

std::forward_list<AbstractPlane> make_sample()
{
	Sphere sample1 = Sphere(0, 0, 0, spr);
	std::forward_list<AbstractPlane> ret = std::forward_list<AbstractPlane>();
	ret.push_front(sample1);
}

Point cp(int x, int y, int z)
{
	return Point(x, y, z);
}

Vector cv(int x, int y, int z)
{
	return Vector(x, y, z);
}

Vector down_vector()
{
	return cv(0, 0, -1);
}

int draw_p(Pointf &p)
{
	return 0;
}
