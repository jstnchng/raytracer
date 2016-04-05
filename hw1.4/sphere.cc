#include <math.h>

#include "sphere.h"
#include "vector.h"

using namespace std;

Sphere::Sphere(Point &o, float r){
	// : Surface(Material m) {
	origin = o;
	radius = r;
}

Intersection Sphere::intersect(Ray &ray) {
	Vector e_c = ray.origin - origin;
	// e_c.print();

	Vector d = ray.dir;
	double d_dot_d = d.dotProduct(d);

	double d_term1 = d.dotProduct(e_c);
	d_term1 *= d_term1;

	double d_term2 = e_c.dotProduct(e_c);
	d_term2 -= (radius*radius);
	d_term2 *= d_dot_d;

	double discriminant = d_term1 - d_term2;

	// std::cout << "discriminant: " << discriminant << std::endl;
	// std::cout << "test" << std::endl;

	if (discriminant < 0.0) {
		return Intersection();
	}

	double sqrt_discrim = sqrt(discriminant);

	double t1 = (d.invert().dotProduct(e_c) + sqrt_discrim) / d_dot_d;
	double t2 = (d.invert().dotProduct(e_c) - sqrt_discrim) / d_dot_d;

	double intersection_t1, intersection_t2;

	if(t1 >= 0.0001 && t2 >= 0.0001){
		intersection_t1 = ((t1>t2) ? t2 : t1);
		intersection_t2 = ((t1>t2) ? t1 : t2);
	} else if (t1 < 0.0001 && t2 < 0.0001){
		return Intersection();
	} else {
		intersection_t1 = ((t1>t2) ? t1 : t2);
		intersection_t2 = intersection_t1;
	}

	bool does_intersect = true;
	// Vector dir_it = ray.dir*intersection_t;
	// Point intersection_pt (ray.origin.x + dir_it.x, ray.origin.y + dir_it.y, ray.origin.z + dir_it.z);
	Point intersection_pt1 = ray.evaluate(intersection_t1);
	Point intersection_pt2 = ray.evaluate(intersection_t2);

	assert(intersection_t1 >= 0.0001);
	assert(intersection_t2 >= 0.0001);
	assert(intersection_t1 <= intersection_t2);

	Vector normal = (intersection_t1>intersection_t2) ? intersection_pt2 - origin : intersection_pt1 - origin;
	// Vector normal = (intersection_t1>intersection_t2) ? intersection_pt1 - origin : intersection_pt2 - origin;
	normal = normal * (1/radius);
	normal.normalize();

	return Intersection(does_intersect, intersection_t1, intersection_t2, intersection_pt1, intersection_pt2, normal);
}

void Sphere::init(Point &o, float r){
	origin = o;
	radius = r;
}

void Sphere::print(){
	cout << "sphere {" << endl;
	cout << "  origin " << origin.x << ", " << origin.y << ", " << origin.z << ">" << endl;
	cout << "  radius <" << radius << ">" << endl;
	cout << "}" << endl;
}