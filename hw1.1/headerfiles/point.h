#ifndef __POINT_H__
#define __POINT_H__

#include "vector.h"

class Point {
	public:
		double x,y,z;

	public:
		Point(){};
		Point(double newX, double newY, double newZ);

		Vector vectorFromPoint(Point p);
		Point multiply(double m);
};

#endif