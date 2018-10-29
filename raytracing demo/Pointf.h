#pragma once
static const float ZERO_MAX = 0.0001f;

class Pointf {

	float x, y, z;
public:
	Pointf();
	Pointf(float a, float b, float c);
	float Pointf::getX() const;
	float Pointf::getY() const;
	float Pointf::getZ() const;
	Pointf Pointf::operator- (const Pointf& c) const;
	Pointf Pointf::operator- ()const;
	Pointf Pointf::operator+ (const Pointf& c) const;
	Pointf Pointf::scale_div(const float div) const;
	Pointf Pointf::scale_mul(const float mul) const;
	Pointf Pointf::reflect_across(Pointf& norm) const;
	Pointf Pointf::cross_product(Pointf &p) const;
	float Pointf::dot_product(const Pointf& c) const;
	float Pointf::magnitude_precise();
	Pointf surf_norm(Pointf& v1, Pointf& v2);
	Pointf Pointf::refract_through(Pointf& norm, float index_of_refraction_1, float index_of_refraction_2);
};