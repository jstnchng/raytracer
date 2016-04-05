#include <math.h>

#include "main.h"
#include "sphere.h"

Sphere::Sphere(Point o, float r){
	this->origin = o;
	this->radius = r;
}

int Sphere::intersect(Ray ray){
	Point p = (origin).multiply(-1);
	Vector x = (ray.origin).vectorFromPoint(p);

	// cout << "Vector: " << x.x << ", " << x.y << ", " << x.z << endl;

	double a = (ray.dir).dotProduct(x);
	double b = pow(a, 2);

	double c = (ray.dir).dotProduct(ray.dir);
	double d = x.dotProduct(x);
	double e = d - pow(radius, 2);

	double f = b - c * e;

	if(f >= 0) {
		std::cout << "discriminant: " << f << endl;
	}

	return f;
}

void Sphere::init(Point o, float r){
	this->origin = o;
	this->radius = r;
}

void Sphere::print(){
	cout << "sphere {" << endl;
	cout << "  origin " << origin.x << ", " << origin.y << ", " << origin.z << ">" << endl;
	cout << "  radius <" << radius << ">" << endl;
	cout << "}" << endl;
}