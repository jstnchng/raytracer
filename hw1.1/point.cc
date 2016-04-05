#include "point.h"
#include "vector.h"

Point::Point(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

Vector Point::vectorFromPoint(Point p){
	double newX = this->x + p.x;
	double newY = this->y + p.y;
	double newZ = this->z + p.z;

	Vector v (newX, newY, newZ);
	return v;
}

Point Point::multiply(double m){
	double newX = this->x * m;
	double newY = this->y * m;
	double newZ = this->z * m;

	Point p (newX, newY, newZ);
	return p;
}
