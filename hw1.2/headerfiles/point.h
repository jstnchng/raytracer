#ifndef __POINT_H__
#define __POINT_H__

#include <cassert>
#include <iostream>
#include <cmath>

#include "vector.h"

using std::istream;
using std::ostream;

class Point {
	public:
		double x,y,z;

	public:
		Point(){};
		Point(double newX, double newY, double newZ);

		void print();

		double operator[] (const int i) const;
		Vector operator- (const Point p) const;
		Vector operator+ (const Point p) const;
		Point operator* (double m);

		Vector toVector();

		friend  istream &operator>>(istream &is, Point &p) {
     	   return is >> p.x >> p.y >> p.z;
    	}
    
    	friend ostream &operator<<(ostream &os, Point &p) {
        	return os<<"<"<<p.x<<","<<p.y<<","<<p.z<<">";
    	}
};

#endif