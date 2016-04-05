#include <math.h>

#include "vector.h"

Vector::Vector(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

double Vector::length(){
	double length = sqrt( pow(x, 2) + pow(y, 2) + pow(z, 2) );
	return length;
}

void Vector::normalize(){
	double length = Vector::length();
	x = x/length;
	y = y/length;
	z = z/length;
}

Vector Vector::crossProduct(Vector vector){
	double cpX = this->y * vector.z - this->z * vector.y;
	double cpY = this->z * vector.x - this->x * vector.z;
	double cpZ = this->x * vector.y - this->y * vector.x;
	Vector cp (cpX, cpY, cpZ);
	return cp; 
}

double Vector::dotProduct(Vector vector){
	return this->x * vector.x + this->y * vector.y + this->z * vector.z;
}

Vector Vector::multiply(double m){
	double newX = x * m;
	double newY = y * m;
	double newZ = z * m;

	Vector v (newX, newY, newZ);
	return v;
}

Vector Vector::add(Vector vector){
	double newX = x + vector.x;
	double newY = y + vector.y;
	double newZ = z + vector.z;

	Vector v (newX, newY, newZ);
	return v;
}