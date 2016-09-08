#include "pointlight.h"

PointLight::PointLight(double r, double g, double b, Point &p)
	: Light(r,g,b){
		pos = p;
		type = 'p';
}

void PointLight::print(){
	std::cout << "p_light {" << std::endl;
	std::cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << std::endl;
	std::cout << "  point: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
	std::cout << "	type: " << type << std::endl;
	std::cout << "}" << std::endl;
}

Vector PointLight::getLightDir(Point &intersectionPt){
	Vector light_dir = pos - intersectionPt;
	light_dir.normalize();
	return light_dir;
}

double PointLight::getDistance(Point &intersectionPt){
	Vector light_dir = pos - intersectionPt;
	return light_dir.length();
}