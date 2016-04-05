#include "intersection.h"

Intersection::Intersection(){
	does_intersect = false;
}

Intersection::Intersection(bool di, double it1, double it2, Point ip1, Point ip2, Vector n, Material m){
	does_intersect = di;
	intersection_t1 = it1;
	intersection_t2 = it2;
	intersection_pt1 = ip1;
	intersection_pt2 = ip2;
	normal = n;
	material = m;
}

Point Intersection::get_closer_ipt(){
	if (intersection_t1 >= 0.0 && intersection_t2 >= 0.0){
		return ((intersection_t1 > intersection_t2) ? intersection_pt2 : intersection_pt1);
	} else if (intersection_t1 < 0.0 && intersection_t2 < 0.0){
		return Point();
	} else {
		return ((intersection_t1>intersection_t2) ? intersection_pt1 : intersection_pt2);
	}
}