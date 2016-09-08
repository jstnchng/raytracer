#ifndef __AREALIGHT_H__
#define __AREALIGHT_H__

#include "light.h"

class AreaLight : public Light {
	public:
		Point center;
		Vector normal;
		Vector u;
		Vector v;
		double len;

	public:
		AreaLight(){};
		AreaLight(Point &c, Vector &n, Vector &u, double &l, double &r, double &g, double &b);
		virtual void print();
		virtual Vector getLightDir(Point &intersectionPt);
		virtual double getDistance(Point &intersectionPt);
};

#endif