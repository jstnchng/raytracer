#ifndef __RAY_H__
#define __RAY_H__

#include <string>

#include "point.h"
#include "vector.h"

class Ray {
	public:
		Point origin;
		Vector dir;
		std::string type;

	public:
		Ray(){};
		Ray(Point &origin, Vector &dir, std::string t);
		void print();
		Point evaluate(double t);
};

#endif