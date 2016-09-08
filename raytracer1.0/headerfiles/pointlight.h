#ifndef __POINTLIGHT_H__
#define __POINTLIGHT_H__

#include "light.h"

class PointLight : public Light {
	public:
		Point pos;
	public:
		PointLight(){};
		PointLight(double r, double g, double b, Point &p);
		virtual void print();
		virtual Vector getLightDir(Point &intersectionPt);
		virtual double getDistance(Point &intersectionPt);
};

#endif