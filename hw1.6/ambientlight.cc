#include <iostream>

#include "ambientlight.h"

using namespace std;

AmbientLight::AmbientLight(){
	rgb.r = 0.;
	rgb.g = 0.;
	rgb.b = 0.;
}

AmbientLight::AmbientLight(double r, double g, double b){
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

void AmbientLight::print(){
	cout << "ambient light {" << endl;
	cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << endl;
	cout << "}" << endl;
}

void AmbientLight::init(double r, double g, double b){
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}