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

XRay::XRay(Pointf const & src_, Pointf const & dir_, float index_of_refraction_, float intensity_) {
	this->dir = dir_.normalize();
	this->src = src_;
	this->intensity = intensity_;
	this->length = -1;
	this->generation = 0;
	this->current_index_of_refraction = index_of_refraction_;
	this->optical_distance = 0;
}

XRay::XRay(Pointf const & src_, Pointf const & dir_, float index_of_refraction_, float intensity_, short generation_)
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

XRay XRay::reflect(Pointf const &norm, float intensity_refracted) const
{
	Pointf new_dir = this->dir;
	new_dir = new_dir - (norm.scale_mul(2.0f * new_dir.dot_product(norm)));
	XRay res;
	if(intensity_refracted <= 0.0f)
		res = XRay(this->src + this->dir.scale_mul(length), new_dir, this->current_index_of_refraction, this->intensity, generation + 1);
	else//compute intensity from fresnel
	{
		float fresnel_intensity = this->intensity - intensity_refracted;
		res = XRay(this->src + this->dir.scale_mul(length), new_dir, this->current_index_of_refraction, fresnel_intensity, generation + 1);
	}
	return res;
}

XRay XRay::refract(Pointf const &norm, const float index_of_refraction, bool s_polarized) const
{
	Pointf new_dir;
	float refract_index = this->current_index_of_refraction / index_of_refraction;
	float vector_dot = dir.dot_product(-norm);
	float radicand = 1 - refract_index * refract_index * (1 - vector_dot * vector_dot);
	
	//if radicand is less than 0, there is total internal reflection--- return an invalid XRay
	if (radicand < 0) return XRay();

	radicand = sqrt(radicand); // stored for later
	new_dir = dir.scale_mul(refract_index) + norm.scale_mul(refract_index * vector_dot - radicand);

	//fresnel intensity computation
	float fresnel_intensity = 2 * current_index_of_refraction * radicand;
	if (s_polarized)
	{
		fresnel_intensity = fresnel_intensity / (current_index_of_refraction * radicand + index_of_refraction * norm.dot_product(new_dir));
	}
	else // p-polarized
	{
		fresnel_intensity = fresnel_intensity / (index_of_refraction * radicand + current_index_of_refraction * norm.dot_product(new_dir));
	}
	

	return XRay(src + dir.scale_mul(length), new_dir, index_of_refraction, fresnel_intensity, generation);
}

//the only place that the data of an XRay can be mutated
int XRay::set_length(const float dist)
{
	if (dist < 0)
		return -1;
	this->length = dist;
	return 0;
}