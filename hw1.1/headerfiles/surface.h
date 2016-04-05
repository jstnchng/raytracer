#ifndef __SURFACE_H__
#define __SURFACE_H__

#include "ray.h"

class Surface {
	public:
		virtual int intersect(Ray ray) { 
			cout << "i am in surface" << endl; 
			return 0;
		};
};

#endif