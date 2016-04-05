#ifndef __AMBIENTLIGHT_H__
#define __AMBIENTLIGHT_H__

#include "rgb.h"

class AmbientLight{
	public:
		Rgb rgb;
	public:
		AmbientLight();
		AmbientLight(double r, double g, double b);
		void print();
		void init(double r, double g, double b);
};

#endif