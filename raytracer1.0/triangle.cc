#include "triangle.h"

Triangle::Triangle(Point &p_1, Point &p_2, Point &p_3){
	p1 = p_1;
	p2 = p_2;
	p3 = p_3;
}

void Triangle::init(Point &p_1, Point &p_2, Point &p_3){
	p1 = p_1;
	p2 = p_2;
	p3 = p_3;	
}

void Triangle::print(){
	cout << "triangle { " << endl;
	cout << "  point 1: ";
	p1.print();
	cout << "  point 2: ";
	p2.print();
	cout << "  point 3: ";
	p3.print();
	cout << "  bbox " << endl;
	bbox.print();
	cout << "}" << endl;
}

double Triangle::getMin(double &x, double &y, double &z){
    if(x <= y && x <= z){
    	return x;
    } else if (y <= x && y <= z){
    	return y;
    } else {
    	return z;
    }
}

double Triangle::getMax(double &x, double &y, double &z){
    if(x >= y && x >= z){
    	return x;
    } else if (y >= x && y >= z){
    	return y;
    } else {
    	return z;
    }
}

Intersection Triangle::intersect(Ray &ray, bool using_bbox, bool render_bbox){
	if(using_bbox && has_bbox){
		Intersection bbox_intersection = bbox.intersect(ray, materialIndex);
        if(!bbox_intersection.does_intersect){
			return Intersection();
		} else if (render_bbox == true) {
			return bbox_intersection;
		}
	}

	Vector p1_p2 = p1-p2;
	double a = p1_p2[0];
	double b = p1_p2[1];
	double c = p1_p2[2];

	Vector p1_p3 = p1-p3;
	double d = p1_p3[0];
	double e = p1_p3[1];
	double f = p1_p3[2];

	double g = ray.dir[0];
	double h = ray.dir[1];
	double i = ray.dir[2];

	Vector p1_origin = p1-ray.origin;
	double j = p1_origin[0];
	double k = p1_origin[1];
	double l = p1_origin[2];

	double ei_hf = e*i - h*f;
	double gf_di = g*f - d*i;
	double dh_eg = d*h - e*g;
	double M = a*ei_hf + b*gf_di + c*dh_eg;

	double ak_jb = a*k - j*b;
	double jc_al = j*c - a*l;
	double bl_kc = b*l - k*c;

	double gamma = (i*ak_jb + h*jc_al + g*bl_kc)/M;
	if (gamma<0 || gamma>1){
		return Intersection();
	}

	double beta = (j*ei_hf + k*gf_di + l*dh_eg)/M;
	if (beta<0 || beta > (1-gamma)){
		return Intersection();
	}

	double t = -1 * (f*ak_jb + e*jc_al + d*bl_kc)/M;
	if(t < 0){
		return Intersection();
	}	

	bool does_intersect = true;
	Point intersection_pt1 = ray.evaluate(t);

	Vector p3_p2 = p3-p2;
	Vector normal = p3_p2.crossProduct(p1_p2);
	normal.normalize();

	Intersection intersection(does_intersect, t, t, intersection_pt1, intersection_pt1, normal, materialIndex);
	return intersection;
}

void Triangle::set_bbox(){
	double scale = 0.0001;

	Point min(getMin(p1.x, p2.x, p3.x)-scale, getMin(p1.y, p2.y, p3.y)-scale, getMin(p1.z, p2.z, p3.z)-scale);
	Point max(getMax(p1.x, p2.x, p3.x)+scale, getMax(p1.y, p2.y, p3.y)+scale, getMax(p1.z, p2.z, p3.z)+scale);

	bbox.init(min, max);
	has_bbox = true;
}



