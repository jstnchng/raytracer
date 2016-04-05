#include <iostream>

#include "camera.h"

using namespace std;

Camera::Camera(Point eye, float d, Vector u, Vector v, Vector w, int nx, int ny, float width, float height){
	this->eye = eye;
	this->d = d;
	this->u = u;
	this->v = v;
	this->w = w;
	this->nx = nx;
	this->ny = ny;
	this->width = width;
	this->height = height;
}

void Camera::init(double x, double y, double z, float d, double vx, double vy, double vz, int nx, int ny, float width, float height){
	Vector D (vx, vy, vz);
	Point eye(x,y,z); 
	Vector up(0,1,0);
	Vector u = D.crossProduct(up);
	Vector v = u.crossProduct(D);
	Vector w ( D.x*-1, D.y*-1, D.z*-1 );
	u.normalize();
	v.normalize();
	w.normalize();

	this->eye = eye;
	this->d = d;
	this->u = u;
	this->v = v;
	this->w = w;
	this->nx = nx;
	this->ny = ny;
	this->width = width;
	this->height = height;
}

void Camera::print(){
	cout << "camera {" << endl;
	cout << "  eye " << this->eye.x << ", " << this->eye.y << ", " << this->eye.z << ">" << endl;
	cout << "  u <" << this->u.x << ", " << this->u.y << ", " << this->u.z << ">" << endl;
	cout << "  v <" << this->v.x << ", " << this->v.y << ", " << this->v.z << ">" << endl;
	cout << "  w <" << this->w.x << ", " << this->w.y << ", " << this->w.z << ">" << endl;
	cout << "  d <" << this->d << ">" << endl;
	cout << "  nx <" << this->ny << ">" << endl;
	cout << "  ny <" << this->nx << ">" << endl;
	cout << "  width <" << this->width << ">" << endl;
	cout << "  height <" << this->height << ">" << endl;
	cout << "}" << endl;
}
