#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "point.h"
#include "vector.h"

class Camera {
	public:
		Point eye;

		float d;

		Vector u;
		Vector v;
		Vector w;

		int nx;
		int ny;

		float width,height;

	public: 
		Camera(){};
		Camera(Point eye, float d, Vector u, Vector v, Vector w, int nx, int ny, float width, float height);
		void init(double x, double y, double z, float d, double vx, double vy, double vz, int nx, int ny, float width, float height);
		void print();
};

#endif