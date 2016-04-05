#ifndef __PLANE_H__
#define __PLANE_H__

#include "surface.h"
#include "vector.h"
#include "point.h"
#include "intersection.h"

using namespace std;

class Plane: public Surface {
	public:
		Vector normal;
		double distanceToOrigin;

	public:
		Plane(){};
		~Plane();
		Plane(Vector &n, double d);
		
		void init(Vector &n, double d);
		Plane planeFromPoints(Point &p1, Point &p2, Point &p3);
		virtual Intersection intersect(Ray &ray);
		virtual void print();
};

#endif