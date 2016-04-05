#include <float.h>

#include "light.h"

using namespace std;

Light::Light(double r, double g, double b){
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

Vector Light::getLightDir (Point &intersectionPt) {
    std::cout << "error: Light::getLightDir should not be called - it's virtual!"<< std::endl;
    
    return Vector();
}

double Light::getDistance (Point &intersectionPt) {
    std::cout << "error: Light::getDistance should not be called - it's virtual!"<< std::endl;
    
    return 0.0;
}

P_Light::P_Light(double r, double g, double b, Point &p)
	: Light(r,g,b){
		pos = p;
}

void P_Light::print(){
	cout << "p_light {" << endl;
	cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << endl;
	cout << "  point: " << pos.x << ", " << pos.y << ", " << pos.z << endl;
	cout << "}" << endl;
}

Vector P_Light::getLightDir(Point &intersectionPt){
	Vector light_dir = pos - intersectionPt;
	light_dir.normalize();
	return light_dir;
}

double P_Light::getDistance(Point &intersectionPt){
	Vector light_dir = pos - intersectionPt;
	return light_dir.length();
}

D_Light::D_Light(double r, double g, double b, Vector &d)
	: Light(r,g,b){
		dir = d;
		dir.normalize();
}

void D_Light::print(){
	cout << "p_light {" << endl;
	cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << endl;
	cout << "  direction: " << dir.x << ", " << dir.y << ", " << dir.z << endl;
	cout << "}" << endl;
}

Vector D_Light::getLightDir(Point &intersectionPt){
	dir.normalize();
	return dir;
}

double D_Light::getDistance(Point &intersectionPt){
	return DBL_MAX;
}

