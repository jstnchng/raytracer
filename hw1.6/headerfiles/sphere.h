#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "surface.h"
#include "point.h"
#include "ray.h"
#include "intersection.h"
#include "bbox.h"

class Sphere: public Surface {
	public:
		Point origin;
		float radius;

	public:
		Sphere(){};
		~Sphere();
		Sphere(Point &o, float r);

		void init(Point &o, float r);
		virtual Intersection intersect(Ray &ray, bool using_bbox, bool render_bbox);
		virtual void set_bbox();
		virtual void print();
};

#endif