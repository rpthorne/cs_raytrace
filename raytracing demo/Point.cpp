#include "Point.h"

Point::Point() : AbstractPoint(float, float, float)
{
}

Point::Point(const float x, const float y, const float z) : AbstractPoint(x, y, z)
{
}
