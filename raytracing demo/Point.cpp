#include "Point.h"
#include <math.h>

Point::Point() : AbstractPoint(0.0, 0.0, 0.0) {}

Point::Point(const float x, const float y, const float z) : AbstractPoint(x, y, z){}

Point Point::operator- (Point &c) const
{
	Point res;
	res.x = this->x - c.x;
	res.y = this->y - c.y;
	res.z = this->z - c.z;
	return res;
}

Point Point::operator- () const
{
	Point res = { -x,-y,-z };
	return res;
}

Point Point::operator- (Point& c) const
{
	return new Point(this->x - c.x, this->y - c.y, this->z - c.z);
}

Point Point::operator+ (Point &c) const
{
	Point res;
	res.x = this->x + c.x;
	res.y = this->y + c.y;
	res.z = this->z + c.z;
	return res;
}

Vector Point::pointToVector() const {
	float magnitude = sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
	return new Vector(this->x / magnitude, this->y / magnitude, this->z / magnitude);
}
