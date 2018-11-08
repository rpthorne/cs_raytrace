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

float Vector::dotProduct(Pointf &v) { 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}
