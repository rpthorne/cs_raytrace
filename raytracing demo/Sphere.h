#pragma once

#include"Point.h"
#include"Vector.h"
#include"XRay.h"
class Sphere {
public:
	float x, y, z, r;
	Point o;
	Sphere();
	Sphere(float x, float y, float z, float r);
	float Sphere::getX();
	float Sphere::getY();
	float Sphere::getZ();
	bool Sphere::onSurface(Point p);
	Vector Sphere::normalAt(Point p);
	int Sphere::collide(XRay x, float &t, Point &p);
};
