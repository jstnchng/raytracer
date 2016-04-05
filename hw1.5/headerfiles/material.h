#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "vector.h"
#include "rgb.h"
#include "light.h"
#include "intersection.h"
#include "ray.h"
#include "point.h"

class Material {
	public:	
		Rgb diffuse_c;
		Rgb specular_c;
		Rgb ideal_specular_c;

		double phong_exp;

	public:
		Material();
		Material(double dcr, double dcg, double dcb, double sr, double sg, double sb, double r, double ir, double ig, double ib);
		Material(Vector &dc, Vector &sc, double r, Vector &isc);

		void setMaterial(double dcr, double dcg, double dcb, double sr, double sg, double sb, double r, double ir, double ig, double ib);
		void print();

		Rgb phongShading(Vector &v, Light* light, Intersection &intersection);

};

#endif