#pragma once
#include "AbstractPoint.h"
class Point :
	public AbstractPoint
{
public:

	Point(const float x, const float y, const float z);
	getX();
	getY();
	getZ();
};

