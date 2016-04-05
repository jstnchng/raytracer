#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "point.h"
#include "vector.h"

class Intersection {
	public:
		bool does_intersect;
		double intersection_t1;
		double intersection_t2;
		Point intersection_pt1;
		Point intersection_pt2;
		Vector normal;

	public:
		Intersection ();
		Intersection (bool di, double it1, double it2, Point ip1, Point ip2, Vector n);

		Point get_closer_ipt();
		double get_smaller_it();
};

#endif