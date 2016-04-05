#include "plane.h"

Plane::Plane(Vector n, double d, Material m){
	normal = n;
	distanceToOrigin = d;
	material = m;
}

void Plane::init(Vector n, double d, Material m){
	normal = n;
	distanceToOrigin = d;
	material = m;
}

//finish plane intersection
Intersection Plane::intersect(Ray &ray) {
    double ray_normal = ray.dir.dotProduct(normal);
    if(ray_normal == 0){
		return Intersection();    	
    } 

    double t_numer = -1 * (ray.origin.toVector().dotProduct(normal) + distanceToOrigin);
    double intersection_t = t_numer/ray_normal;
    Point intersection_pt = ray.evaluate(intersection_t);

    if(intersection_t < 0.0){
    	return Intersection();
    }

    return Intersection(true, intersection_t, intersection_t, intersection_pt, intersection_pt, normal, material);
}

Plane planeFromPoints(Point p1, Point p2, Point p3, Material m){
	Vector a = p2-p1;
	Vector b = p3-p1;
	Vector n = a.crossProduct(b);
	double d = p1.toVector().dotProduct(n);

	return Plane(n, -1*d, m);
}


void Plane::print(){
	cout << "plane {" << endl;
	cout << "  normal " << normal.x << ", " << normal.y << ", " << normal.z << ">" << endl;
	cout << "  distance to origin <" << distanceToOrigin << ">" << endl;
	cout << "}" << endl;
}


