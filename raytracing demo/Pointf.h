#pragma once
static const float ZERO_MAX = 0.0001f;

class Pointf {

	float x, y, z;
public:

	//constructors

	Pointf();
	Pointf(float a, float b, float c);

	//getters

	float Pointf::getX() const;
	float Pointf::getY() const;
	float Pointf::getZ() const;
	float Pointf::magnitude_precise() const;

	//mathematical operations on points

	Pointf Pointf::operator- (const Pointf& c) const;
	Pointf Pointf::operator- () const;
	Pointf Pointf::operator+ (const Pointf& c) const;
	Pointf Pointf::scale_div(const float div) const;
	Pointf Pointf::scale_mul(const float mul) const;
	float Pointf::dot_product(const Pointf& c) const;
	Pointf surf_norm(const Pointf& v1, const Pointf& v2) const;
	Pointf normalize() const;
	Pointf Pointf::cross_product(Pointf &p) const;

	//depricated
	Pointf Pointf::reflect_across(Pointf& norm) const;
	Pointf Pointf::refract_through(Pointf& norm, float index_of_refraction_1, float index_of_refraction_2);
};