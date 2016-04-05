#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "ray.h"
#include "material.h"
#include "intersection.h"

class Surface {
	// public:
		// Material material;

	public:
		// Surface(Material m){material = m};
		// virtual ~Surface();
		virtual Intersection intersect(Ray &ray);
		// void setMaterial(Material m){material = m};
};

#endif