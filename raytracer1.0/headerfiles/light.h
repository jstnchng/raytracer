#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "point.h"
#include "rgb.h"
#include "vector.h"

class Light{
	public:
		Rgb rgb;
		char type;
	public:
		Light(){};
		virtual ~Light(){};
		Light(double r, double g, double b);
		virtual Vector getLightDir(Point &intersectionPt);
		virtual void print(){};
		virtual double getDistance(Point &intersectionPt);
};

#endif