#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cassert>
#include <iostream>
#include <cmath>

using std::istream;
using std::ostream;

// class Point;

class Vector {
	public:
		double x;
		double y;
		double z;

	public:
		Vector(){};
		Vector(double newX, double newY, double newZ);
		void set(double newX, double newY, double newZ);

		void print();

		double length();
		void normalize();

		double operator[] (const int i) const;
		
		Vector crossProduct(Vector vector);
		double dotProduct(Vector vector);
		
		Vector operator+ (const Vector &vector) const;
		Vector operator* (const double scale) const;
		Vector invert() const;

		// Point toPoint();

		friend istream &operator>>(istream &is, Vector &v) {
       		return is>>v.x>>v.y>>v.z;
    	}
    
    	friend ostream &operator<<(ostream &os, Vector &v) {
        	return os<<"<"<<v.x<<","<<v.y<<","<<v.z<<">";
    	}

};

#endif