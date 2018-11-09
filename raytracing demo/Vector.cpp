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

Vector Vector::reflect(Vector &norm)
{
	Vector res;
	res.x = this->x;
	res.y = this->y;
	res.z = this->z;
	//res = res - (norm.scale_mul(2.0f * this->dot_product(norm)));//TODO needs updating
	return res;
}

//assumes norm  normal
//returns a normalized vector corresponding to the refracted direction
Vector Vector::refract(Vector &norm, float index_of_refraction_1, float index_of_refraction_2)
{
	/*
	//normalize this
	Pointf p = normalize();
	Pointf result;
	float refract_index = index_of_refraction_1 / index_of_refraction_2;
	float vector_dot = v.dot_product(-norm);
	result = p.scale_mul(refract_index) + norm.scale_mul(refract_index * vector_dot - sqrt(1 - refract_index * refract_index * (1 - vector_dot * vector_dot)));
	return result;
	*/ //TODO needs updating, will look at tongiht
}
