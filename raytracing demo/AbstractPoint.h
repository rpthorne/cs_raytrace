#pragma once

class AbstractPoint
{
	float x, y, z;
public:
	AbstractPlane(const float x, const float y, const float z) {
		this->x = x;
		this->y = y;
		this->z = z;	
	}

	float getX() const { return this->x } 
	float getY() const { return this->y }
	float getZ() const { return this->z }
};
