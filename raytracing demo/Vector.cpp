#include "Vector.h"

Vector::Vector() : AbstractPoint(float, float, float)
{
}

Vector::Vector(const float x, const float y, const float z) : AbstractPoint(x, y, z)
{
}

float Vector::getX() { return this->x }
float Vector::getY() { return this->y }
float Vector::getZ() { return this->z }

float Vector::getMagnitude() {
	return sqrtf(this->dot_product(*this));
}

float Vector::dotProduct(Pointf &v) { 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}

Vector Vector::scaleDiv(const float div)
{
	Vector res;
	res.x = this->x / div;
	res.y = this->y / div;
	res.z = this->z / div;
	return res;
}

Vector Vector::scaleMul(const float mul)
{
	Vector res;
	res.x = this->x * mul;
	res.y = this->y * mul;
	res.z = this->z * mul;
	return res;
}

Vector Vector::normalize()
{
	return scaleDiv(getMagnitude());
}
