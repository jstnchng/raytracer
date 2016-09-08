#include "arealight.h"

AreaLight::AreaLight(Point &c, Vector &n, Vector &u, double &l, double &r, double &g, double &b)
	: Light(r,g,b){
	center = c;
	normal = n;
	normal.normalize();
	this->u = u;
	this->u.normalize();
	v = u.crossProduct(n);
	v.normalize();
	len = l;
	type = 'a';
}

void AreaLight::print(){
	std::cout << "area light {" << std::endl;
	std::cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << std::endl;
	std::cout << "  normal: " << normal.x << ", " << normal.y << ", " << normal.z << std::endl;
	std::cout << "  u: " << u.x << ", " << u.y << ", " << u.z << std::endl;
	std::cout << "  v: " << v.x << ", " << v.y << ", " << v.z << std::endl;
	std::cout << "	type: " << type << std::endl;
	std::cout << "	length: " << len << std::endl;
	std::cout << "}" << std::endl;
}

Vector AreaLight::getLightDir(Point &intersectionPt){
	std::cout << "warning: AreaLight::getLightDir shouldn't actually be called" << std::endl;;
	return Vector();
}

double AreaLight::getDistance(Point &intersectionPt){
	std::cout << "warning: AreaLight::getDistance shouldn't actually be called" << std::endl;;
	return -1;
}
