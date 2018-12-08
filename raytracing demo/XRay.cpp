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
#include "XRay.h"
#include <math.h>
#include <stdlib.h>
#include "TrianglePlane.h"

//macro for magnitude so i dont have to type that shit
#define SQR_MAG(mag_point) (mag_point.getX() * mag_point.getX() + mag_point.getY() * mag_point.getY() + mag_point.getZ() * mag_point.getZ()) 

//constructors
XRay::XRay() {
	this->dir = Vector();
	this->src = Point();
	this->intensity = 0;
	this->length = -1;
	this->generation = 0;
	this->current_index_of_refraction = 1;
	this->optical_pathlength = 0;
}

XRay::XRay(Point const &src_, Vector const &dir_, Vector const &wave_dir_, float index_of_refraction_, float intensity_) {
	this->dir = dir_;
	this->src = src_;
	this->wave_dir = wave_dir_;
	this->intensity = intensity_;
	this->length = -1;
	this->generation = 0;
	this->current_index_of_refraction = index_of_refraction_;
	this->optical_pathlength = 0;
}

XRay::XRay(Point const & src_, Vector const & dir_, Vector const &wave_dir_, float index_of_refraction_, float intensity_, short generation_, float optical_pathlength_)
{
	this->dir = dir_;
	this->src = src_;
	this->wave_dir = wave_dir_;
	this->intensity = intensity_;
	this->length = -1;
	this->generation = generation_;
	this->current_index_of_refraction = index_of_refraction_;
	this->optical_pathlength = optical_pathlength_;
}

//getters
const Vector XRay::get_dir() const { return this->dir; }

const Point XRay::get_src() const { return this->src; }

const Vector XRay::get_wave_dir() const	{	return this->wave_dir;}

float XRay::get_intensity() const { return this->intensity; }

float XRay::get_optic_pathlength() const {return this->optical_pathlength + this->length * this->current_index_of_refraction;}

float XRay::get_length() const { return this->length; }



//setters and creaters

int XRay::collide(XRay* reflect, XRay* refract, Vector const &norm, const float index_of_refraction)
{
	Vector refl_dir = this->dir;
	refl_dir = Vector(refl_dir.traverse(1) - (norm.traverse(2.0f * refl_dir.dot_product(norm))));
	reflect = (XRay*)malloc(sizeof(XRay));
	Point collision_point = dir.traverse(length);
	Vector s_direction = TrianglePlane(collision_point, src, collision_point + norm.traverse(1)).get_normal();
	Vector p_direction = TrianglePlane(collision_point, dir, s_direction).get_normal(); 
	float s_component = wave_dir.dot_product(s_direction);//% along s_dir that intensity is
	float p_component = wave_dir.dot_product(s_direction);
	//fresenl that stuff
	//p_direction
	float costheti = -this->dir.dot_product(norm);
	//p_component = ((index_of_refraction * costheti - current_index_of_refraction * costhett) / (index_of_refraction * costheti - current_index_of_refraction * costhett));
	p_component = p_component * p_component * this->wave_dir.dot_product(s_direction);
	//s_component = ((index_of_refraction * costhett - current_index_of_refraction * costheti) / (index_of_refraction * costhett - current_index_of_refraction * costheti));
	s_component = s_component * s_component * wave_dir.dot_product(s_direction);
	Point refl_i = s_direction.traverse(s_component) + p_direction.traverse(p_component);
	return 0;
}

//currently assuming no total internal reflections.
XRay XRay::reflect(Vector &norm) const
{
	Vector new_dir = this->dir;
	new_dir = Vector(new_dir.traverse(1) - (norm.traverse(2.0f * new_dir.dot_product(norm))));
	XRay res;
	//first direction of p-wave
	Vector poi = norm.cross_product(dir);
	Vector p_dir = poi.cross_product(dir);
	Point p_component = p_dir.traverse(p_dir.dot_product(wave_dir) * intensity);
	float p_intensity = sqrtf(SQR_MAG(p_component));
	Point s_component = wave_dir.traverse(intensity) - p_component;
	float s_intensity = sqrtf(SQR_MAG(s_component));
	p_dir = norm.cross_product(new_dir);//set p_dir to the new p_dir
	//initials are computed
	

	//now compute magnutude of nex pieces

	//now compute fresnel intensity 
	res = XRay(this->src + this->dir.traverse(length), new_dir, this->wave_dir, this->current_index_of_refraction, this->intensity, generation + 1, get_optic_pathlength());
	return res;
}

XRay XRay::refract(Vector const &norm, const float index_of_refraction) const
{
	Vector new_dir;
	float refract_index = this->current_index_of_refraction / index_of_refraction;
	float vector_dot = this->dir.dot_product(-norm);
	float radicand = 1 - refract_index * refract_index * (1 - vector_dot * vector_dot);
	
	//if radicand is less than 0, there is total internal reflection--- return an invalid XRay
	if (radicand < 0) return XRay();

	radicand = sqrt(radicand); // stored for later
	new_dir = Vector(dir.traverse(refract_index) + norm.traverse(refract_index * vector_dot - radicand));

	//fresnel intensity computation
	float fresnel_intensity = 2 * current_index_of_refraction * radicand;
	fresnel_intensity = fresnel_intensity / (current_index_of_refraction * radicand + index_of_refraction * norm.dot_product(new_dir));

	

	return XRay(src + dir.traverse(length), new_dir, this->wave_dir, index_of_refraction, fresnel_intensity, generation, get_optic_pathlength());
}

//the only place that the data of an XRay can be mutated
int XRay::set_length(const float dist)
{
	if (dist < 0)
		return -1;
	this->length = dist;
	return 0;
}
