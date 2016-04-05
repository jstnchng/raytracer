#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "surface.h"
#include "vector.h"
#include "point.h"
#include "intersection.h"

using namespace std;

class Triangle: public Surface {
	public:
		Point p1;
		Point p2;
		Point p3;

	public:
		Triangle(){};
		~Triangle();
		Triangle(Point &p_1, Point &p_2, Point &p_3);
		
		void init(Point &p_1, Point &p_2, Point &p_3);
		virtual Intersection intersect(Ray &ray);
		virtual void print();
};

#endif