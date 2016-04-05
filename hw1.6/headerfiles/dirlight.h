#ifndef __DIRLIGHT_H__
#define __DIRLIGHT_H__

#include "light.h"

class DirLight : public Light {
	public:
		Vector dir;
	public:
		DirLight(){};
		DirLight(double r, double g, double b, Vector &d);
		virtual void print();
		virtual Vector getLightDir(Point &intersectionPt);
		virtual double getDistance(Point &intersectionPt);
};


#endif