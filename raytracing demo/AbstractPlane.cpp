#include "AbstractPlane.h"
#include "Pointf.h"

Pointf AbstractPlane::get_normal()
{
	return normal;
}


float AbstractPlane::get_determinant(Pointf &a, Pointf &b, Pointf &c)
{
	return a.getX() * b.getY() * c.getZ() + a.getZ() * b.getX() * c.getY() + a.getY() * b.getZ() * c.getX() - \
		a.getX() * b.getZ() * c.getY() - a.getY() * b.getX() * c.getZ() - a.getZ() * b.getY() * c.getX();
}