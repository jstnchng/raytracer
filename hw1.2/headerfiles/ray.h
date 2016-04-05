#ifndef __RAY_H__
#define __RAY_H__

#include "point.h"
#include "vector.h"

class Ray {
	public:
		Point origin;
		Vector dir;

	public:
		Ray(){};
		Ray(Point origin, Vector dir);
		void print();
		Point evaluate(double t);
};

#endif