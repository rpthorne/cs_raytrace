#include "XRay.h"
#include <math.h>




//constructors
XRay::XRay() {
	this->dir = Pointf();
	this->src = Pointf();
	this->intensity = 0;
	this->length = -1;
	this->generation = 0;
	this->current_index_of_refraction = 1;
	this->optical_distance = 0;
}

XRay::XRay(Pointf const & src_, Pointf const & dir_, const float index_of_refraction_, float const & intensity_) {
	this->dir = dir_.normalize();
	this->src = src_;
	this->intensity = intensity_;
	this->length = -1;
	this->generation = 0;
	this->current_index_of_refraction = index_of_refraction_;
	this->optical_distance = 0;
}

XRay::XRay(Pointf const & src_, Pointf const & dir_, const float index_of_refraction_, float const intensity_, int const generation_)
{
	this->dir = dir_.normalize();
	this->src = src_;
	this->intensity = intensity_;
	this->length = -1;
	this->generation = generation_;
	this->current_index_of_refraction = index_of_refraction_;
	this->optical_distance = 0;
}

//getters
const Pointf XRay::get_dir() const { return this->dir; }

const Pointf XRay::get_src() const { return this->dir; }

float XRay::get_intensity() const { return this->intensity; }

float XRay::get_optic_path_length() const {return this->optical_distance + this->length * this->current_index_of_refraction;}

float XRay::get_length() const { return this->length; }

//setters and creaters

XRay XRay::reflect(Pointf const &norm, const int total_internal) const
{
	Pointf new_dir = this->dir;
	new_dir = new_dir - (norm.scale_mul(2.0f * new_dir.dot_product(norm)));
	XRay res;
	if(total_internal)
		res = XRay(this->src + this->dir.scale_mul(length), new_dir, this->current_index_of_refraction, this->intensity, generation + 1);
	else//compute intensity from fresnel
	{

		res = XRay(this->src + this->dir.scale_mul(length), new_dir, this->current_index_of_refraction, this->intensity, generation + 1);
	}
	return res;
}

XRay XRay::refract(Pointf const &norm, const float index_of_refraction) const
{
	//if(inbound 

	//normalize this
	Pointf p = dir.scale_mul(sqrtf(dir.dot_product(dir)));
	Pointf result;
	float refract_index = this->current_index_of_refraction / index_of_refraction;
	float vector_dot = p.dot_product(-norm);
	result = p.scale_mul(refract_index) + norm.scale_mul(refract_index * vector_dot - sqrt(1 - refract_index * refract_index * (1 - vector_dot * vector_dot)));
	return result;
}

//the only place that the data of an XRay can be mutated
int XRay::set_length(const float dist)
{
	if (dist < 0)
		return -1;
	this->length = dist;
	return 0;
}