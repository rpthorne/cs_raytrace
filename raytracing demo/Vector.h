/****************************************************************
* Vector is a class representing a normalized vector, in that the 
* 3 points represent directional magnitude on each axis from the 
* origin
*****************************************************************/

#pragma once
#include "AbstractPoint.h"
#include "Point.h"
class Vector :
	public AbstractPoint
{
public:
	
	Vector();
	Vector(const float x, const float y, const float z);

	float getMagnitude() const;
	float dotProduct(Vector &v) const;
	Vector operator- () const;
	Vector crossProduct(Vector &v) const;
	Point traverse(float d) const;
};

