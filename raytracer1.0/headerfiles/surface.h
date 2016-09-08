#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "ray.h"
#include "intersection.h"
#include "bbox.h"

class Surface {
	public:
		int materialIndex;
		BBox bbox;
		bool has_bbox;

	public:
		virtual Intersection intersect(Ray &ray, bool using_bbox, bool render_bbox);
		virtual void set_bbox(){
			has_bbox = false;
		}

		// default constructor give it the default material
    	Surface () { materialIndex = 0; }

    	void setMaterialIndex(int mi){
    		materialIndex = mi;
    	}

    	virtual void print(){};
};

#endif	