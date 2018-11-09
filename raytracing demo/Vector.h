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
	
	Vector(const float x, const float y, const float z);

	float getMagnitude();
	float dotProduct(Vector v);
	Vector crossProduct(Vector &v);
};

