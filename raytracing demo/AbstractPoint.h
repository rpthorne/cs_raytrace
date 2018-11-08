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

	float getX() { return this->x }
	float getY() { return this->y }
	float getZ() { return this->z }
};
