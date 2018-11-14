#include"Sphere.h"
#include<Math.h>
#include"Point.h"
#include"Point.cpp"
#include"Vector.h"
#include"XRay.h"
#include"XRay.cpp"

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
	Vector m = x.get_src() - this->o;
	float b = m.dotProduct(x.get_dir());
	float c = (m.dotProduct(m) - (this->r * this->r));

	//exit if r's origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
		return 0;

	float discr = b * b - c;

	//negative discriminant means ray missed sphere
	if (discr < 0.0f) return 0; //there was not an intersection

	//shortest distance t of intersection with sphere
	t = -b - Sqrt(discr);
	
	//if t is negative (rounding error?), force 0
	if (t < 0.0f)
		t = 0.0f;
	Vector dir = x.get_dir();
	Point d = new Point(dir.getX() * t, dir.getY() * t, dir.getZ() * t);
	p = x.get_src() + d;

	n = this->normalAt(p);

	return 1; //there was an intersection
}
