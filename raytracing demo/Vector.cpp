#include "Vector.h"

Vector::Vector() : AbstractPoint(float, float, float){}

Vector::Vector() : AbstractPoint(0.0, 0.0, 0.0){}

Vector::Vector(const float x, const float y, const float z) : AbstractPoint(x, y, z){}

float Vector::getMagnitude() {
	return sqrtf(this->dotProduct(*this));
}

float Vector::dotProduct(Vector &v) { 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}

Vector Vector::crossProduct(Vector &v)
{
	return Vector(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
Vector Vector::operator-() {
	return new Vector(this->getX() * -1, this->getY() * -1, this->getZ() * -1);
}

Point Vector::traverse(float d) {
	return new Point(this->x * d, this->y * d, this->z * d);
}