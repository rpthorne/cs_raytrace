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
#include "DetectorPlate.h"
#include "Sphere.h"
#include "Raygun.h"
#include <forward_list>
#include <list>
#include <queue>

#ifndef ZERO_MAX
#define ZERO_MAX (0.0001f)
#endif // !ZERO_MAX


//#defs for the simulation, these are run-time constants for the simulation,
//if you wish to change them in a derived class, simple #define them before #including this file

//detector plate size, from the origin
#ifndef DETECTOR_PLATE_SIZE
#define DETECTOR_PLATE_SIZE (5.0f)
#endif // !DETECTOR_PLATE_SIZE

//detector plate depth
#ifndef DETECTOR_PLATE_DEPTH
#define DETECTOR_PLATE_DEPTH (2.0f)
#endif

//detector plate width, in pixels
#ifndef DETECTOR_PLATE_WIDTH
#define DETECTOR_PLATE_WIDTH (100)
#endif

//detector plate height, in pixels
#ifndef DETECTOR_PLATE_HEIGHT
#define DETECTOR_PLATE_HEIGHT (100)
#endif

//sphere radius
#ifndef SPHERE_RADIUS
#define SPHERE_RADIUS (1.0f)
#endif

//camera source depth
#ifndef CAMERA_SOURCE_DEPTH
#define CAMERA_SOURCE_DEPTH (5.0f)
#endif

//camera source depth
#ifndef CAMERA_SOURCE_WIDTH
#define CAMERA_SOURCE_WIDTH (2)
#endif

//camera source depth
#ifndef CAMERA_SOURCE_HEIGHT
#define CAMERA_SOURCE_HEIGHT (2)
#endif

//field of view in degrees
#ifndef FIELD_OF_VIEW_DEGREES
#define FIELD_OF_VIEW_DEGREES (30.0f)
#endif

//aspect ratio
#ifndef ASPECT_RATIO
#define ASPECT_RATIO (1.0f)
#endif

//xray count horizontally
#ifndef XRAY_COUNT_HORIZONTAL
#define XRAY_COUNT_HORIZONTAL (100)
#endif

//xray count vertically
#ifndef XRAY_COUNT_VERTICAL
#define XRAY_COUNT_VERTICAL (100)
#endif

//initial index of refraction
#ifndef DEFAULT_INDEX_OF_REFRACTION
#define DEFAULT_INDEX_OF_REFRACTION (1.0f)
#endif

//samples index of refraction
#ifndef SAMPLE_INDEX_OF_REFRACTION
#define SAMPLE_INDEX_OF_REFRACTION (1.1f)
#endif // !SAMPLE_INDEX_OF_REFRACTION


//initial intensity
#ifndef INITIAL_INTENSITY
#define INITIAL_INTENSITY (1.0f)
#endif

class simulation
{
protected:
	std::forward_list<Sphere> sample;
	Raygun camera;
	DetectorPlate detector_plate;

	//list to keep track of -ALL- XRays in the scene
	std::queue<XRay, std::list<XRay>> xray_list;
public:
	//reccommend overriding these in graphical applications
	virtual int draw_p(Point &p);
	virtual int draw_ray(XRay &x);

	//constructors
	simulation();

	float get_ior(XRay &p);

	int run_scene();

	//here we output data from simulation, if it needs to be done
	virtual int clean_scene(deplentry **results);

};
