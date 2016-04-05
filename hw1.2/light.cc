#include "light.h"

using namespace std;

Light::Light(double r, double g, double b){
	// Rgb n_rgb (r, g, b);
	// rgb = n_rgb;
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
}

P_Light::P_Light(double r, double g, double b, Point p)
	: Light(r,g,b){
		pos = p;
}

void P_Light::print(){
	cout << "p_light {" << endl;
	cout << "  rgb: " << rgb.r << ", " << rgb.g << ", " << rgb.b << endl;
	cout << "  point: " << pos.x << ", " << pos.y << ", " << pos.z << endl;
	cout << "}" << endl;
}