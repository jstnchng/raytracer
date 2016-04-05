#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "surface.h"
#include "vector.h"
#include "point.h"
#include "intersection.h"
#include "bbox.h"

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

		double getMin(double &x, double &y, double &z);
		double getMax(double &x, double &y, double &z);
		
		void init(Point &p_1, Point &p_2, Point &p_3);
		virtual Intersection intersect(Ray &ray, bool using_bbox, bool render_bbox);
		virtual void set_bbox();
		virtual void print();
};

#endif