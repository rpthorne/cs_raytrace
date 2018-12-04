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
 ****************************************************************/

#pragma once
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
	int Sphere::collision(XRay x, float &t, Point &p, Vector &n);
};
