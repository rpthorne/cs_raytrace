/****************************************************************
 *	Vector
 *
 *	A vector represents a 3-dimensional point that has a distance
 * to the origin of exactly 1. in other words, it is normalized.
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once
#include "Vector.h"
#include <math.h>

Vector::Vector() : AbstractPoint(0.0, 0.0, 0.0){}

Vector::Vector(const float x, const float y, const float z) : AbstractPoint(x, y, z){}

Vector::Vector(Point p) : AbstractPoint(p.getX(), p.getY(), p.getZ()){
	float magnitude = sqrtf(p.getX() * p.getX() + p.getY() * p.getY() + p.getZ() * p.getZ());
	this->x = this->x / magnitude;
	this->y = this->y / magnitude;
	this->z = this->z / magnitude;
}

float Vector::get_magnitude() {
	return sqrtf(this->dot_product(*this));
}

float Vector::dot_product(Vector const &v) const{ 
	return this->x * v.x + this->y * v.y + this->z * v.z; 
}

Vector Vector::cross_product(Vector const &v) const
{
	return Vector(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z, this->x * v.y - this->y * v.x);
}
Vector Vector::operator-() const {
	return Vector(this->getX() * -1, this->getY() * -1, this->getZ() * -1);
}

Point Vector::traverse(float d) const {
	return Point(this->x * d, this->y * d, this->z * d);
}
