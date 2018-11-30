/****************************************************************
 *	Point
 *
 *	Point class inherits the AbstractPoint class. It contains a
 * default constructor, standard constructor requiring 3 floats,
 * as well as some overriding operator methods: Binary + and - as
 * well as unary -. Also contains a method to return the magnitude
 * of the point as if it were a normalized vector.
 *
 ****************************************************************/

#include "Point.h"
#include <math.h>

Point::Point() : AbstractPoint(0.0, 0.0, 0.0) {}

Point::Point(const float x, const float y, const float z) : AbstractPoint(x, y, z){}

Point Point::operator- () const {
	Point res = { -x,-y,-z };
	return res;
}

Point Point::operator- (Point const &c) const {
	return Point(this->x - c.x, this->y - c.y, this->z - c.z);
}

Point Point::operator+ (Point const &c) const
{
	Point res;
	res.x = this->x + c.x;
	res.y = this->y + c.y;
	res.z = this->z + c.z;
	return res;
}

float Point::get_magnitude() {
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}
