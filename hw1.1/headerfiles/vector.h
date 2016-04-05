#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector {
	public:
		double x;
		double y;
		double z;

	public:
		Vector(){};
		Vector(double newX, double newY, double newZ);

		double length();
		void normalize();
		
		Vector crossProduct(Vector vector);
		double dotProduct(Vector vector);
		
		Vector add(Vector vector);
		Vector multiply(double m);

};

#endif