/****************************************************************
 *	className
 *
 *	description of class
 *
 ****************************************************************/

#include"Sphere.h"
#pragma once
#include<math.h>

Sphere::Sphere() { x = 0; y = 0; z = 0; r = 0; o = Point(0.0, 0.0, 0.0); };
Sphere::Sphere(float x, float y, float z, float r) { this->x = x; this->y = y; this->z = z; this->r = r; o = Point(x, y, z); }

float Sphere::getX() { return this->x; }
float Sphere::getY() { return this->y; }
float Sphere::getZ() { return this->z; }

bool Sphere::onSurface(Point p) {
	if (sqrt((p.getX() * p.getX()) + (p.getY() * p.getY()) + (p.getZ() * p.getZ())) == r)
		return true;
	else
		return false;
}

Vector Sphere::normalAt(Point p) {
	if (!onSurface(p))
		return (Vector(0, 0, 0));
	return Vector(p.getX(), p.getY(), p.getZ());
}

int Sphere::collision(XRay x, float &t, Point &p, Vector &n) {
	Point tmp = Point(x.get_src().getX() - this->o.getX(), x.get_src().getY() - this->o.getY(), x.get_src().getZ() - this->o.getZ());
	Vector m = Vector(tmp);
	float b = m.dot_product(x.get_dir());
	float c = (m.dot_product(m) - (this->r * this->r));

	//exit if r's origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
		return 0;

	float discr = b * b - c;

	//negative discriminant means ray missed sphere
	if (discr < 0.0f) return 0; //there was not an intersection

	//shortest distance t of intersection with sphere
	t = -b - sqrtf(discr);
	
	//if t is negative (rounding error?), force 0
	if (t < 0.0f)
		t = 0.0f;
	Vector dir = x.get_dir();
	Point d = Point(dir.getX() * t, dir.getY() * t, dir.getZ() * t);
	p = x.get_src() + d;

	n = this->normalAt(p);

	return 1; //there was an intersection
}
