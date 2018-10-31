#include "AbstractPlane.h"
#include "Pointf.h"

Pointf AbstractPlane::get_normal() const
{
	return normal;
}


float AbstractPlane::get_determinant(const Pointf &a, const Pointf &b, const Pointf &c) const
{
	return a.getX() * b.getY() * c.getZ() + a.getZ() * b.getX() * c.getY() + a.getY() * b.getZ() * c.getX() - \
		a.getX() * b.getZ() * c.getY() - a.getY() * b.getX() * c.getZ() - a.getZ() * b.getY() * c.getX();
}