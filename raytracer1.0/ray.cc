#include "ray.h"

using namespace std;

Ray::Ray(Point &origin, Vector &dir, string t){
	this->origin = origin;
	this->dir = dir;
	type = t;
}

Point Ray::evaluate(double t){
	Vector dir_t = dir*t;
	Point p (origin[0] + dir_t[0], origin[1] + dir_t[1], origin[2] + dir_t[2]);
	return p;
}

void Ray::print(){
	cout << "Origin: " << "<" << origin[0] << ", " << origin[1] << ", " << origin[2] << ">" << endl;
	cout << "Direction: " << "<" << dir[0] << ", " << dir[1] << ", " << dir[2] << ">" << endl;
}
