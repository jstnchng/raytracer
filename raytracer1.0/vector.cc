#include <math.h>

#include "vector.h"

using namespace std;

Vector::Vector(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

void Vector::print(){
	cout << "Vector: " << x << ", " << y << ", " << z << endl;
}

void Vector::set(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

double Vector::length(){
	double length = sqrt(x*x + y*y + z*z);
	return length;
}

void Vector::normalize(){
	double length = Vector::length();
	if(length != 1){
		x = x/length;
		y = y/length;
		z = z/length;
	}
}

double Vector::operator[](const int i) const{
	assert( i >= 0 && i < 3);
	if(i==0){
		return x;
	} else if(i==1){
		return y;
	} else {
		return z;
	}
}

Vector Vector::crossProduct(const Vector &vector) const{
	double cpX = this->y * vector[2] - this->z * vector[1];
	double cpY = this->z * vector[0] - this->x * vector[2];
	double cpZ = this->x * vector[1] - this->y * vector[0];
	Vector cp (cpX, cpY, cpZ);
	return cp; 
}

double Vector::dotProduct(const Vector &vector) const{
	return this->x * vector[0] + this->y * vector[1] + this->z * vector[2];
}

Vector Vector::invert() const{
	return operator*(-1.0);
}

// Point Vector::toPoint(){
// 	Point p (x,y,z);
// 	return p;
// }

Vector Vector::operator+(const Vector &vector) const{
	double newX = x + vector.x;
	double newY = y + vector.y;
	double newZ = z + vector.z;

	Vector v (newX, newY, newZ);
	return v;
}

Vector Vector::operator-(const Vector &vector) const{
	double newX = x - vector.x;
	double newY = y - vector.y;
	double newZ = z - vector.z;

	Vector v (newX, newY, newZ);
	return v;
}

Vector Vector::operator*(const double scale) const{
	double newX = x * scale;
	double newY = y * scale;
	double newZ = z * scale;

	Vector v (newX, newY, newZ);
	return v;
}

Vector &Vector::operator+=(const Vector &vector){
	x = x + vector.x;
	y = y + vector.y;
    z = z + vector.z;
        
    return *this;
}

Vector &Vector::operator-=(const Vector &vector){
	x = x - vector.x;
	y = y - vector.y;
    z = z - vector.z;
        
    return *this;
}

Vector &Vector::operator*=(const double scale){
	x = x * scale;
	y = y * scale;
    z = z * scale;
        
    return *this;
}



