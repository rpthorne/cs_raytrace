#pragma once

#include"Pointf.h"
#include"XRay.h"
class Sphere {
public:
	float x, y, z, r;
	Pointf o;
	Sphere();
	Sphere(float x, float y, float z, float r);
	float Sphere::getX();
	float Sphere::getY();
	float Sphere::getZ();
	bool Sphere::onSurface(Pointf p);
	Pointf Sphere::normalAt(Pointf p);
};
