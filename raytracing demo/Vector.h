/****************************************************************
* Vector is a class representing a normalized vector, in that the 
* 3 points represent directional magnitude on each axis from the 
* origin
*****************************************************************/

#pragma once
#include "AbstractPoint.h"
class Vector :
	public AbstractPoint
{
public:
	
	Vector();
	Vector(const float x, const float y, const float z);

	float Vector::getMagnitude();
	float Vector::dotProduct(Vector &v);
	Vector Vector::crossProduct(Vector &v);
	Point Vector::traverse(float d);
};

