#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "surface.h"
#include "point.h"
#include "ray.h"

class Sphere: public Surface {
	public:
		Point origin;
		float radius;

	public:
		Sphere(){};
		Sphere(Point o, float r);
		void init(Point o, float r);
		int intersect(Ray ray);
		void print();
};

#endif