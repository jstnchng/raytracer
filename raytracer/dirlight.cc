#include <float.h>

#include "dirlight.h"

DirLight::DirLight(double r, double g, double b, Vector &d)
	: Light(r,g,b){
		dir = d;
		dir.normalize();
		type = 'd';
}

void DirLight::print(){
	std::cout << "p_light {" << std::endl;
	std::cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << std::endl;
	std::cout << "  direction: " << dir.x << ", " << dir.y << ", " << dir.z << std::endl;
	std::cout << "	type: " << type << std::endl;
	std::cout << "}" << std::endl;
}

Vector DirLight::getLightDir(Point &intersectionPt){
	dir.normalize();
	return dir;
}

double DirLight::getDistance(Point &intersectionPt){
	return DBL_MAX;
}