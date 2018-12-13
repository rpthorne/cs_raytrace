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
#include "AbstractPoint.h"
#include "Point.h"

class Vector :
	public AbstractPoint
{
public:
	
	//an invalid vector, it points in no direction and has length 0
	Vector();
	//for both constructors, the represented point will be normalized
	Vector(const float x, const float y, const float z);
	Vector(Point p);

	float get_magnitude(); // always 1
	float dot_product(Vector const &v) const;
	Vector cross_product(Vector const &v) const;
	
	//inverts the direction of the vector
	Vector operator- () const; 

	//finds a point in 3-d space that represents this vector with magnitude d
	Point traverse(float d) const;
};

