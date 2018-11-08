#include "Point.h"

Point::Point() : AbstractPoint(float, float, float)
{
}

Point::Point(const float x, const float y, const float z) : AbstractPoint(x, y, z)
{
}

float Point::getX() { return this->x }
float Point::getY() { return this->y }
float Point::getZ() { return this->z }
