#include"Sphere.h"
#include<Math.h>
#include"Point.h"
#include"Point.cpp"
#include"Vector.h"
#include"XRay.h"
#include"XRay.cpp"

Sphere::Sphere() { x = 0; y = 0; z = 0; r = 0; };
Sphere::Sphere(float x, float y, float z, float r) { this->x = x; this->y = y; this->z = z; this->r = r; o = Point(x, y, z); }

float Sphere::getX() { return this->x; }
float Sphere::getY() { return this->y; }
float Sphere::getZ() { return this->z; }

bool Sphere::onSurface(Point p) {
	if (sqrt((p.getX() ^ 2) + (p.getY() ^ 2) + (p.getZ() ^ 2)) == r)
		return true;
	else
		return false;
}

Vector Sphere::normalAt(Point p) {
	if (!onSurface(p))
		return (Vector(0, 0, 0));
	return Vector(p.getX(), p.getY(), p.getZ());
}
