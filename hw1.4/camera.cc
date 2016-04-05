#include <iostream>
#include <fstream>
#include <float.h>
#include <assert.h>
#include <cstddef>
#include <cstring>
#include <math.h>

#include "camera.h"

using namespace std;

void Camera::init(Point &pos, Vector &dir, float d, float iw, float ih, int pw, int ph){
	eye = pos;
	
	w = dir.invert();
	w.normalize();

	Vector up(0,1,0);

	// make an orthonormal frame for the camera:
    if (1.0 - fabs (w[1]) < .0001) {
        // camera is pointing up or down - make an arbitrary
        // right-handed coordinate system:
        u.set(1.0, 0.0, 0.0);
        v = w.crossProduct(u);
    }
    else {
        Vector up (0., 1., 0.);
        u = dir.crossProduct(up);
        v = u.crossProduct(dir);
    }

    u.normalize ();
    v.normalize ();

	focal_length = d;
	pixels_width = pw;
	pixels_height = ph;
	image_width = iw;
	image_height = ih;

	try {
    	pixelBuffer.resizeErase(pixels_height, pixels_width);    
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}

void Camera::print(){
	cout << "camera {" << endl;
	cout << "  eye <" << this->eye.x << ", " << this->eye.y << ", " << this->eye.z << ">" << endl;
	cout << "  u <" << this->u.x << ", " << this->u.y << ", " << this->u.z << ">" << endl;
	cout << "  v <" << this->v.x << ", " << this->v.y << ", " << this->v.z << ">" << endl;
	cout << "  w <" << this->w.x << ", " << this->w.y << ", " << this->w.z << ">" << endl;
	cout << "  focal_length <" << focal_length << ">" << endl;
	cout << "  pixels width <" << pixels_width << ">" << endl;
	cout << "  pixels height <" << pixels_height << ">" << endl;
	cout << "  image width <" << image_width << ">" << endl;
	cout << "  image height <" << image_height << ">" << endl;
	cout << "}" << endl;
}

Ray Camera::generateRay (const int i, const int j){
	double r = image_width/2.0;
	double l = -1. * r;
	double t = image_height/2.0;
	double b = -1. * t;

	double u = l + (r-l) * (i+.5) / pixels_width;
	double v = t + (b-t) * (j+.5) / pixels_height;

	Vector dw = w * -1.0 * focal_length;
	Vector uu = this->u * u;
    Vector vv = this->v * v;

	Vector dir = dw + uu + vv;

	dir.normalize();

    Ray ray (eye, dir, "PRIMARY");

	return ray;
}

void Camera::renderScene (
		std::vector< Surface * > &surfaces,
		std::vector< Light * > &lights,
		std::vector< Material * > &materials,
        AmbientLight &ambient_light){
	std::cout << "rendering" << endl;

	int printProgress = pixels_width * pixels_height / 10.0;

    Rgb black(0,0,0);

    // int first_xx = 1000000;
    // int first_yy = 1000000;

	ofstream myfile;
  	myfile.open ("output.txt");

	for(int xx=0; xx< pixels_width; xx++){
		for(int yy=0; yy< pixels_height; yy++){		
    // for(int xx=69; xx< 70; xx++){
        // for(int yy=223; yy< 224; yy++){                                        
			if ((yy * pixels_width + xx) % printProgress == 0){
            	std::cout << ".";
        	}	

        	Ray ray = generateRay(xx, yy);

            Rgb color = calculateRgb(ray, 0, DBL_MAX, 10, ambient_light, surfaces, lights, materials);

            setPixel (xx, yy, color);  
		}
	}

	std::cout << std::endl;

	std::cout << "done rendering" << std::endl;
}

Rgb Camera::calculateRgb(Ray &ray, double min_t, double max_t, 
        int recurse_limit,
        AmbientLight &ambient_light,
        std::vector< Surface * > &surfaces,
        std::vector< Light * > &lights,
        std::vector< Material * > &materials){

    if (recurse_limit == 0){
        return Rgb();
    }

    //shadow rays
    if (ray.type == "SHADOW"){
        bool is_shadow = false;

        for( int j=0; j<surfaces.size(); j++){
            Surface *s = surfaces[j];
            Intersection intersection = s->intersect(ray);

            if(intersection.does_intersect 
                    && intersection.get_smaller_it() > min_t
                    && intersection.get_smaller_it() < max_t){
                is_shadow = true;
            } 
        }

        if(is_shadow){
            return Rgb();
        } else {
            return Rgb(1,1,1);
        }
    }

    //find closest intersection
    bool foundIntersection = false;
    Intersection closest_intersection;
    double smallest_it = DBL_MAX;
    int materialId = 0; 
    
    for(int i=0; i<surfaces.size(); i++){
        Surface *s = surfaces[i];

        Intersection current_i = s->intersect(ray);
        if(current_i.does_intersect 
                && current_i.intersection_t1 > min_t
                && current_i.intersection_t1 < max_t){
            foundIntersection = true;

            if(current_i.intersection_t1 < smallest_it) {
                closest_intersection = current_i;
                smallest_it = current_i.intersection_t1;
                materialId = s->materialIndex;
            } 
            if(current_i.intersection_t2 < smallest_it) {
                closest_intersection = current_i;
                smallest_it = current_i.intersection_t2;
                materialId = s->materialIndex;
            }
        }
    }

    if(!foundIntersection){
        return Rgb();
    }

    Point closest_ipt = ray.evaluate(smallest_it);
    assert(smallest_it > 0.0001);

    assert(closest_ipt[0] == closest_intersection.get_closer_ipt()[0]);
    assert(closest_ipt[1] == closest_intersection.get_closer_ipt()[1]);
    assert(closest_ipt[2] == closest_intersection.get_closer_ipt()[2]);

    // rgb color calculation
    Rgb color;
    for(int i=0; i<lights.size(); i++){
        Vector light_dir = lights[i]->getLightDir(closest_ipt);
        Ray shadow_ray (closest_ipt, light_dir, "SHADOW");
        double distance_to_light = lights[i]->getDistance(closest_ipt);

        Rgb shadow_rgb = calculateRgb(shadow_ray, 0.0001, distance_to_light, 1, ambient_light, surfaces, lights, materials);

        // check if in shadow, calculate blinn phong
        Vector v = ray.dir.invert();
        if (!shadow_rgb.isZero()){
            
            Rgb li;

            li = materials[materialId]->phongShading(v, lights[i], closest_intersection);
            
            color += li;
        }

        // send recursive reflective ray
        if(! (materials[materialId]->ideal_specular_c.isZero()) ) {
            Vector n = closest_intersection.normal;
            double scale = 2 * (n.dotProduct(v));
            Vector r = n*scale - v;
            r.normalize();

            Ray reflective_ray (closest_ipt, r, "REFLECTIVE");

            color += ( materials[materialId]->ideal_specular_c * 
                calculateRgb(reflective_ray, 0.0001, DBL_MAX, recurse_limit-1, ambient_light, surfaces, lights, materials) );
        }
    }

    // add ambient
    if(ray.type == "PRIMARY"){
        color += materials[materialId]->diffuse_c * ambient_light.rgb;
    }

    return color;
}

void Camera::writeImage (const char *sceneFile){
    try {
    	RgbaOutputFile file (sceneFile, pixels_width, pixels_height, WRITE_RGBA);
    	file.setFrameBuffer (&pixelBuffer[0][0], 1, pixels_width);
	    file.writePixels (pixels_height);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return;
    }
}






