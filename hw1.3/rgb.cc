#include <iostream>

#include "rgb.h"

using namespace std;

Rgb::Rgb(){
	r = 0.;
	g = 0.;
	b = 0.;
}

Rgb::Rgb(double re, double gr, double bl){
	r = re;
	g = gr;
	b = bl;
}

void Rgb::print(){
	cout << "rgb: " << r << ", " << g << ", " << b << endl;
}

Rgb Rgb::operator- (const Rgb rgb) const{
	double newR = r - rgb.r;
	double newG = g - rgb.g;
	double newB = b - rgb.b;

	Rgb new_rgb (newR, newG, newB);
	return new_rgb;
}

Rgb Rgb::operator+ (const Rgb rgb) const{
	double newR = r + rgb.r;
	double newG = g + rgb.g;
	double newB = b + rgb.b;

	Rgb new_rgb (newR, newG, newB);
	return new_rgb;
}

Rgb Rgb::operator* (const Rgb rgb) const{
	double newR = r * rgb.r;
	double newG = g * rgb.g;
	double newB = b * rgb.b;

	Rgb new_rgb (newR, newG, newB);
	return new_rgb;
}

Rgb Rgb::operator* (double scale){
	double newR = r * scale;
	double newG = g * scale;
	double newB = b * scale;

	Rgb new_rgb (newR, newG, newB);
	return new_rgb;
}


