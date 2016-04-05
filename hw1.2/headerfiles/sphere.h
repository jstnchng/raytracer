#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "surface.h"
#include "point.h"
#include "ray.h"
#include "material.h"
#include "intersection.h"

class Sphere: public Surface {
	public:
		Point origin;
		float radius;
		Material material;

	public:
		Sphere(){};
		~Sphere();
		Sphere(Point o, float r, Material m);

		void init(Point o, float r, Material m);
		virtual Intersection intersect(Ray &ray);
		void print();
};

#endif