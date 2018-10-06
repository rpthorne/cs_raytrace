#pragma once

struct PointfA
{
	float x, y, z;
};


class Pointf {
public:

	Pointf Pointf::scale_div(const float div) const;
	Pointf Pointf::scale_mul(const float mul) const;
	Pointf Pointf::reflect_across(Pointf norm) const;
	float Pointf::dot_product(const Pointf& c) const;
	PointfA Pointf::asArray();
	Pointf Pointf::reflect_across(Pointf norm) const;
	float Pointf::magnitude_precise();
	Pointf surf_norm(Pointf base, Pointf v1, Pointf v2);
};