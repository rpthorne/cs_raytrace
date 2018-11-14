#include "Point.h"

Point::Point() : AbstractPoint(float, float, float)
{
}

Point::Point(const float x, const float y, const float z) : AbstractPoint(x, y, z)
{
}

Point Point::operator- (Point &c)
{
	Point res;
	res.x = this->x - c.x;
	res.y = this->y - c.y;
	res.z = this->z - c.z;
	return res;
}

Point Point::operator- ()
{
	Point res = { -x,-y,-z };
	return res;
}

Point Point::operator- (Point& c)
{
	return new Point(this->x - c.x, this->y - c.y, this->z - c.z);
}

Point Point::operator+ (Point &c)
{
	Point res;
	res.x = this->x + c.x;
	res.y = this->y + c.y;
	res.z = this->z + c.z;
	return res;
}
