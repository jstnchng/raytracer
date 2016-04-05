#include "point.h"

using namespace std;

Point::Point(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

void Point::init(double x, double y, double z){
	this->x = x;
	this->y = y; 
	this->z = z;
}

void Point::print(){
	cout << "point: " << x << ", " << y << ", " << z << endl;
}

double Point::operator[](const int i) const{
	assert( i >= 0 && i < 3);
	if(i==0){
		return x;
	} else if(i==1){
		return y;
	} else {
		return z;
	}
}

Vector Point::operator- (const Point &p) const{
	double newX = this->x - p.x;
	double newY = this->y - p.y;
	double newZ = this->z - p.z;

	Vector v (newX, newY, newZ);
	return v;
}

Vector Point::operator+ (const Point &p) const{
	double newX = this->x + p.x;
	double newY = this->y + p.y;
	double newZ = this->z + p.z;

	Vector v (newX, newY, newZ);
	return v;
}

Point Point::operator+ (const double d) const{
	double newX = x+d;
	double newY = y+d;
	double newZ = z+d;

	Point p (newX, newY, newZ);
	return p;
}

Point Point::operator*(double m){
	double newX = this->x * m;
	double newY = this->y * m;
	double newZ = this->z * m;

	Point p (newX, newY, newZ);
	return p;
}

Point Point::operator+ (const Vector &v) const{
	double newX = x+v.x;
	double newY = y+v.y;
	double newZ = z+v.z;

	Point p (newX, newY, newZ);
	return p;
}

Point Point::operator- (const Vector &v) const{
	double newX = x-v.x;
	double newY = y-v.y;
	double newZ = z-v.z;

	Point p (newX, newY, newZ);
	return p;
}

Vector Point::toVector(){
	Vector v (x,y,z);
	return v;
}

