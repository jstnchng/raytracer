#ifndef __BBOX_H__
#define __BBOX_H__

#include "point.h"
#include "ray.h"
#include "intersection.h"
#include <iostream>

class BBox {
	public: 
		Point min;
		Point max;
		int surface_index;

	public:
		BBox();
		BBox(Point &min, Point &max, int &surface_index);

		void init(Point &min, Point &max);
		Intersection intersect(Ray &ray, int materialId);
		void print();

		Point get_centroid();
};

#endif