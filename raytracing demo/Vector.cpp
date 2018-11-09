#include "Vector.h"

Vector::Vector() : AbstractPoint(float, float, float)
{
}

Vector::Vector(const float x, const float y, const float z) : AbstractPoint(x, y, z)
{
}

float Vector::getMagnitude() {
	return sqrtf(this->dot_product(*this));
}

float Vector::dotProduct(Vector &v) { 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}

Vector Vector::crossProduct(Vector &v)
{
	return Vector(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
