#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "point.h"
#include "rgb.h"

class Light{
	public:
		Rgb rgb;
	public:
		Light(){};
		virtual ~Light(){};
		Light(double r, double g, double b);
};

class P_Light : public Light {
	public:
		Point pos;
	public:
		P_Light(){};
		P_Light(double r, double g, double b, Point p);
		void print();
};

#endif