/****************************************************************
 *	XRay
 *
 *	an XRay models an distinct, discrete X-Ray beam,
 * it is made up of several components. a source point, 
 * representing where this X-ray starts.
 * a dir(ection) and length representing where the Xray collides
 * with something.
 * 
 * a wave direction, describing how the Xray oscilates
 * 
 * an intensity, describing how much energy the XRay can transmit
 *
 * the index of refraction for the medium in which this XRay travels
 *
 * an optical path length which represents the distance this XRay
 * has traveled (impeded by the medium it has traveled in) from
 * when this XRay was produced from a raybox.
 *
 * a genration, indicating how many times this XRay has been reflected.
 * We will not consider an XRay after some n generations
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include "Point.h"
#include "Vector.h"

#ifndef MAX_REFLECTION_COUNT
#define MAX_REFLECTION_COUNT (3)
#endif


//length assumed to be one
class XRay
{
	Point src;
	Vector dir; //guaranteed to be normal
	float length; // absolute length of this ray, not optical length of this ray
	Vector wave_dir; //must be orthagonal to dir, represents the direction fo the amplitude
	float intensity; //describes the magnitude of the amlitude of the wave
	int generation;
	float optical_pathlength;
	float current_index_of_refraction;
	
	//secret constructor for generational tracking
	XRay(Point const &src_, Vector const &dir_, Vector const &wave_dir_, float index_of_refraction_, float intensity_, short generation_, float optical_pathlength_);
public:
	//constructers

	XRay();
	XRay(Point const &src_, Vector const &dir_, Vector const &wave_dir_, float index_of_refraction_, float intensity_);

	//getters

	const Vector get_dir() const;
	const Point get_src() const;
	const Vector get_wave_dir() const;
	float get_intensity() const;
	float get_optic_pathlength() const;
	float get_length() const;
	
	//operations

	int XRay::set_length(const float dist);

	//return codes:
	//0: 2 XRays, all good
	//1: 1 XRay, normal propogatation but reflection has been cut due to excessive generation
	//2: 1 XRay, total internal reflection
	//3: 0 XRays, total internal reflection on a cut reflection
	int XRay::collide(XRay** reflect, XRay** refract, Vector const &norm, const float index_of_refraction);

	//relfect take some output from refract in order to save time
	XRay XRay::reflect(Vector const &norm) const;
	XRay XRay::refract(Vector const &norm, const float index_of_refraction) const;
};
