#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "ray.h"
#include "intersection.h"

class Surface {
	public:
		int materialIndex;

	public:
		virtual Intersection intersect(Ray &ray);

		// default constructor give it the default material
    	Surface () { materialIndex = 0; }

    	void setMaterialIndex(int mi){
    		materialIndex = mi;
    	}

    	virtual void print(){};
};

#endif	