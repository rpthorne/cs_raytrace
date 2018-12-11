/****************************************************************
 *	Abstract Point
 *
 *	Header file for the class AbstractPoint. AbstractPoint is 
 * an object denoted by 3 floats representing the x,y, and z
 * coordinates in three dimensional space of a point. Any class
 * that inherits AbstractPoint will have these three protected 
 * float values, getters for each of these, and a constructor 
 * which takes three float values as parameters.
 *
 * @author
 * Ryan Thorne
 * Nic Cox
 ****************************************************************/

#pragma once

#ifndef ZERO_MAX
#define ZERO_MAX (.00001f)
#endif // !ZERO_MAX


class AbstractPoint
{
protected:
	float x, y, z;
public:
	AbstractPoint(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;	
	}

	float getX() const { return this->x; };
	float getY() const { return this->y; };
	float getZ() const { return this->z; };
};
