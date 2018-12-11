/****************************************************************
 *	Sphere
 *
 *	The Sphere class represents a perfect sphere in 3-dimensional
 * space. It is defined by the 3 float values representing the
 * x,y,z values of the origin and/or an actual Point as per the
 * point class representing the origin, as well as a float value
 * r representing the radius of the sphere. Default constructor
 * is a sphere of radius 0 at the origin, effectively a point.
 * The standard constructor takes 4 floats for x,y,z,r
 * respectively. Getters are defined for the x,y,z coordinates of
 * the origin. A boolean function, onSurface, takes a Point as
 * input and returns a boolean value stating whether that point is
 * on the surface of the sphere. The normalAt function checks if
 * the parameter Point is on the surface, and if so, returns a
 * vector of the normal at that point. Finally, the collision
 * method takes an XRay and pointers to a float, Point, and
 * Vector. The method returns an integer 0 if there is no
 * collision with the sphere from the given XRay, and a 1 if yes.
 * The float pointer is "filled" with the distance from the XRay
 * origin to the collision. The Point pointer is "filled" with
 * the point of collision, and the Vector pointer is the normal
 * vector at the point of collision.
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include"Sphere.h"
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
	//if (!onSurface(p))
	//	return (Vector(0, 0, 0));
	return Vector(p);
}

int Sphere::collision(XRay x, float &t, Point &p, Vector &n) {
	Point tmp = x.get_src() - o;// Point(x.get_src().getX() - this->o.getX(), x.get_src().getY() - this->o.getY(), x.get_src().getZ() - this->o.getZ());
	//only works for rad=1 spheres
	Vector m = Vector(x.get_src() - o);
	float b = 2.0f * m.dot_product(x.get_dir()) * tmp.get_magnitude();
	float c = (tmp.get_magnitude() * tmp.get_magnitude() - (this->r * this->r));

	//exit if r's origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
		return 0;

	float discr = b * b - 4.0 * c;

	//negative discriminant means ray missed sphere
	if (discr < 0.0f) return 0; //there was not an intersection

	discr = sqrtf(discr);//costly square root function
	//shortest distance t of intersection with sphere
	t = -b - discr;
	
	//if t is negative or zero, one point of intersection behind us, use longer value instead
	if (t < ZERO_MAX)
		t += discr + discr;
	t = t * .5f;//all over 2a

	p = x.get_src() + x.get_dir().traverse(t);

	n = this->normalAt(p);

	return 1; //there was an intersection
}
