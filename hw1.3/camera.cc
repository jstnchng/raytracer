#include <iostream>
#include <fstream>
#include <float.h>
#include <assert.h>
#include <cstddef>
#include <cstring>
#include <math.h>

#include "camera.h"

using namespace std;

void Camera::init(Point pos, Vector dir, float d, float iw, float ih, int pw, int ph){
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

	Ray ray (eye, dir);

	return ray;
}

void Camera::renderScene (
		std::vector< Surface * > &surfaces,
		std::vector< Light * > &lights,
		std::vector< Material * > &materials){
	std::cout << "rendering" << endl;

	int printProgress = pixels_width * pixels_height / 10.0;

	int colored_px = 0;
	int total_px = 0;

    Rgb black(0,0,0);

    // int first_xx = 1000000;
    // int first_yy = 1000000;

	ofstream myfile;
  	myfile.open ("output.txt");

	for(int xx=0; xx< pixels_width; xx++){
		for(int yy=0; yy< pixels_height; yy++){		
    // for(int xx=0; xx< 1; xx++){
        // for(int yy=689; yy< 690; yy++){                                        
			if ((yy * pixels_width + xx) % printProgress == 0){
            	std::cout << ".";
        	}	

        	Ray ray = generateRay(xx, yy);

	  		bool foundIntersection = false;
        	Intersection closest_intersection;
        	double smallest_it = DBL_MAX;
        	int materialId = 0; 
            
        	for(int i=0; i<surfaces.size(); i++){
        		Surface *s = surfaces[i];

        		Intersection current_i = s->intersect(ray);
        		if(current_i.does_intersect){
        			foundIntersection = true;
        			if(current_i.intersection_t1 < smallest_it){
        				closest_intersection = current_i;
        				smallest_it = current_i.intersection_t1;
        				materialId = s->materialIndex;
        			} 
        			if(current_i.intersection_t2 < smallest_it){
        				closest_intersection = current_i;
        				smallest_it = current_i.intersection_t2;
        				materialId = s->materialIndex;
        			}
        		}
        	}

        	if(!foundIntersection){
        		setPixel(xx,yy, black);
        		total_px++;
        		continue;
        	}

        	Point closest_ipt = ray.evaluate(smallest_it);
        	assert(closest_ipt[0] == closest_intersection.get_closer_ipt()[0]);
        	assert(closest_ipt[1] == closest_intersection.get_closer_ipt()[1]);
        	assert(closest_ipt[2] == closest_intersection.get_closer_ipt()[2]);

            Rgb color;
            for(int i=0; i<lights.size(); i++){
                Vector light_dir = lights[i]->getLightDir(closest_ipt);
                Ray shadow_ray (closest_ipt, light_dir);

                bool is_shadow = false;
                double distance_to_light = lights[i]->getDistance(closest_ipt);

                for(int j=0; j<surfaces.size(); j++){
                    Surface *s = surfaces[j];
                    Intersection intersection = s->intersect(shadow_ray);

                    if(intersection.does_intersect 
                            && intersection.get_smaller_it() > 0.01 
                            && intersection.get_smaller_it() < distance_to_light){
                        is_shadow = true;
                    }

                }

                if(!is_shadow){
                    Rgb li = materials[materialId]->phongShading(ray, eye, lights[i], closest_intersection);
                    color = color + li; 
                } 
            }

       		setPixel (xx, yy, color);  
       		colored_px++; 
       		total_px++;
		}
	}

	std::cout << std::endl;

	std::cout << "colored pixels: " << colored_px << std::endl;
	std::cout << "total pixels: " << total_px << std::endl;

	std::cout << "done rendering" << std::endl;
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






