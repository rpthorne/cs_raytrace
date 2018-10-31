#include"Sphere.h"
#include<Math.h>
#include"Pointf.h"
#include"Pointf.cpp"
#include"XRay.h"
#include"XRay.cpp"

Sphere::Sphere() { x = 0; y = 0; z = 0; r = 0; };
Sphere::Sphere(float x, float y, float z, float r) { this->x = x; this->y = y; this->z = z; this->r = r; o = Pointf(x, y, z); }

float Sphere::getX() { return this->x; }
float Sphere::getY() { return this->y; }
float Sphere::getZ() { return this->z; }

bool Sphere::onSurface(Pointf p) {
	if (sqrt((p.getX ^ 2) + (p.getY ^ 2) + (p.getZ ^ 2)) == r)
		return true;
	else
		return false;
}

Pointf Sphere::normalAt(Pointf p) {
	if (!onSurface(p))
		return (Pointf(0, 0, 0));
	return p;
}
