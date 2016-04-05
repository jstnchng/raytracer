#ifndef __PLANE_H__
#define __PLANE_H__

#include "surface.h"
#include "vector.h"
#include "point.h"
#include "material.h"
#include "intersection.h"

using namespace std;

class Plane: public Surface {
	public:
		Vector normal;
		double distanceToOrigin;
		Material material;

	public:
		Plane(){};
		~Plane();
		Plane(Vector n, double d, Material m);
		
		void init(Vector n, double d, Material m);
		Plane planeFromPoints(Point p1, Point p2, Point p3, Material m);
		virtual Intersection intersect(Ray &ray);
		void print();
};

#endif