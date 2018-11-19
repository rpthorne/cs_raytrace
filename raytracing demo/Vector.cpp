#include "Vector.h"
#include <math.h>

Vector::Vector() : AbstractPoint(0.0, 0.0, 0.0){}

Vector::Vector(const float x, const float y, const float z) : AbstractPoint(x, y, z){}

float Vector::getMagnitude() {
	return sqrtf(this->dotProduct(*this));
}

float Vector::dotProduct(Vector &v) { 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}

Vector Vector::crossProduct(Vector &v) const
{
	return Vector(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
Vector Vector::operator-() const {
	return Vector(this->getX() * -1, this->getY() * -1, this->getZ() * -1);
}

Point Vector::traverse(float d) const {
	return Point(this->x * d, this->y * d, this->z * d);
}

Vector Vector::pointToVector(Point p) {
	float magnitude = sqrtf(p.getX() * p.getX() + p.getY() * p.getY() + p.getZ() * p.getZ());
	return Vector(this->x / magnitude, this->y / magnitude, this->z / magnitude);
}