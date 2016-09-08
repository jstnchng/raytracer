#include "intersection.h"

Intersection::Intersection(){
	does_intersect = false;
}

Intersection::Intersection (bool di, double it1, double it2, Point &ip1, Point &ip2, Vector &n, int mid){
	does_intersect = di;
	intersection_t1 = it1;
	intersection_t2 = it2;
	intersection_pt1 = ip1;
	intersection_pt2 = ip2;
	normal = n;
	materialId = mid;
}

Point Intersection::get_closer_ipt(){
	if (intersection_t1 >= 0.0001 && intersection_t2 >= 0.0001){
		return ((intersection_t1 > intersection_t2) ? intersection_pt2 : intersection_pt1);
	} else if (intersection_t1 < 0.0001 && intersection_t2 < 0.0001){
		return Point();
	} else {
		return ((intersection_t1>intersection_t2) ? intersection_pt1 : intersection_pt2);
	}
}

double Intersection::get_smaller_it(){
	return ((intersection_t1 > intersection_t2) ? intersection_t2 : intersection_t1);	
}