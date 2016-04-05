#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "point.h"
#include "rgb.h"
#include "vector.h"

class Light{
	public:
		Rgb rgb;
	public:
		Light(){};
		virtual ~Light(){};
		Light(double r, double g, double b);
		virtual Vector getLightDir(Point &intersectionPt);
		virtual void print(){};
		virtual double getDistance(Point &intersectionPt);
};

class P_Light : public Light {
	public:
		Point pos;
	public:
		P_Light(){};
		P_Light(double r, double g, double b, Point &p);
		virtual void print();
		virtual Vector getLightDir(Point &intersectionPt);
		virtual double getDistance(Point &intersectionPt);
};

class D_Light : public Light {
	public:
		Vector dir;
	public:
		D_Light(){};
		D_Light(double r, double g, double b, Vector &d);
		virtual void print();
		virtual Vector getLightDir(Point &intersectionPt);
		virtual double getDistance(Point &intersectionPt);
};

#endif