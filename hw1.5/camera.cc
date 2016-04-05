#include <iostream>
#include <fstream>
#include <float.h>
#include <assert.h>
#include <cstddef>
#include <cstring>
#include <math.h>
#include <algorithm>

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

bool sort_x (BBox *i, BBox *j) { 
    return (i->get_centroid().x < j->get_centroid().x); 
}
bool sort_y (BBox *i, BBox *j) {  
    return (i->get_centroid().y < j->get_centroid().y); 
}
bool sort_z (BBox *i, BBox *j) {  
    return (i->get_centroid().z < j->get_centroid().z); 
}

BVHNode * Camera::build_bvh_tree(std::vector< BBox * > &bboxes, int axis){
    // cout << "segfault 1" << endl;

    BVHNode *tnode = new BVHNode();

    double min_x = DBL_MAX;
    double min_y = DBL_MAX;
    double min_z = DBL_MAX;
    double max_x = -DBL_MAX;
    double max_y = -DBL_MAX;
    double max_z = -DBL_MAX;
    
    // cout << "segfault 2" << endl;

    for (int i=0; i<bboxes.size(); i++){
        if (bboxes[i]->min.x < min_x){
            min_x = bboxes[i]->min.x;
        } if (bboxes[i]->min.y < min_y){
            min_y = bboxes[i]->min.y;
        } if (bboxes[i]->min.z < min_z){
            min_z = bboxes[i]->min.z;
        } 

        if (bboxes[i]->max.x > max_x){
            max_x = bboxes[i]->max.x;
        } if (bboxes[i]->max.y > max_y){
            max_y = bboxes[i]->max.y;
        } if (bboxes[i]->max.z > max_z){
            max_z = bboxes[i]->max.z;
        }
    }

    // cout << "segfault 2.1" << endl;
    Point min (min_x, min_y, min_z);
    Point max (max_x, max_y, max_z);

    tnode->bbox.init(min, max);

    // cout << "segfault 3" << endl;

    if(bboxes.size() == 1){
        //get surface index from surfaces, check first/last
        //create bbox around the original bbox
        //set left/right to null;
        // cout << "segfault 4" << endl;

        tnode->left = nullptr;
        tnode->right = nullptr;
        tnode->bbox = *(bboxes[0]);
        tnode->is_leaf = true;

        return tnode;
    } else {
        // cout << "segfault 5" << endl;

        if (axis == 0){
            std::sort(bboxes.begin(), bboxes.end(), sort_x);
        }
        else if (axis == 1){
            std::sort(bboxes.begin(), bboxes.end(), sort_y);
        }
        else {
            std::sort(bboxes.begin(), bboxes.end(), sort_z);
        } 

        int mid = (bboxes.size()-1)/2;

        std::vector<BBox *> bbox_left;
        std::vector<BBox *> bbox_right;

        // cout << "segfault 6" << endl;

        for (int i = 0; i <= mid; i++){
            bbox_left.push_back(bboxes[i]);
        }
        for (int j = mid+1; j < bboxes.size(); j++){
            bbox_right.push_back(bboxes[j]);
        }

        // cout << "segfault 7" << endl;

        tnode->left = build_bvh_tree(bbox_left, (axis+1)%3);
        tnode->right = build_bvh_tree(bbox_right, (axis+1)%3);

        tnode->bbox.surface_index = -1;
        tnode->is_leaf = false;

        return tnode;
    }
}

void Camera::renderScene (
		std::vector< Surface * > &surfaces,
		std::vector< Light * > &lights,
		std::vector< Material * > &materials,
        AmbientLight &ambient_light,
        bool using_bbox, bool render_bbox, bool using_bvh){
	std::cout << "rendering" << endl;

	int printProgress = pixels_width * pixels_height / 10.0;

    Rgb black(0,0,0);

    // int first_xx = 1000000;
    // int first_yy = 1000000;

	ofstream myfile;
  	myfile.open ("output.txt");

    std::vector<BBox *> bboxes;
    for(int i=0; i<surfaces.size(); i++){
        Surface *s = surfaces[i];
        (s->bbox).surface_index = i;
        bboxes.push_back( &(s->bbox) );
    }

    BVHNode* bvh_root = build_bvh_tree(bboxes, 0);

	for(int xx=0; xx< pixels_width; xx++){
		for(int yy=0; yy< pixels_height; yy++){		
    // for(int xx=69; xx< 70; xx++){
        // for(int yy=223; yy< 224; yy++){                                        
			if ((yy * pixels_width + xx) % printProgress == 0){
            	std::cout << "." << std::endl;
        	}	

        	Ray ray = generateRay(xx, yy);

            Rgb color = calculateRgb(ray, 0, DBL_MAX, 20, ambient_light, bvh_root, surfaces, lights, materials, using_bbox, render_bbox, using_bvh);

            setPixel (xx, yy, color);  
		}
	}

    bboxes.clear();

	std::cout << std::endl;

	std::cout << "done rendering" << std::endl;
}

Rgb Camera::calculateRgb(Ray &ray, double min_t, double max_t, 
        int recurse_limit,
        AmbientLight &ambient_light,
        BVHNode * bvh_root,
        std::vector< Surface * > &surfaces,
        std::vector< Light * > &lights,
        std::vector< Material * > &materials,
        bool using_bbox, bool render_bbox, bool using_bvh){

    if (recurse_limit == 0){
        return Rgb();
    }

    //shadow rays
    if (ray.type == "SHADOW"){
        bool is_shadow = false;

        if (using_bvh){
            Intersection intersection = bvh_root->intersect(ray, DBL_MAX, surfaces, using_bbox, render_bbox);
            if(intersection.does_intersect && intersection.get_smaller_it() > min_t && intersection.get_smaller_it() < max_t){
                is_shadow = true;
            }
        } else {
            for( int j=0; j<surfaces.size(); j++){
                Surface *s = surfaces[j];
                Intersection intersection = s->intersect(ray, using_bbox, render_bbox);

                if(intersection.does_intersect 
                        && intersection.get_smaller_it() > min_t
                        && intersection.get_smaller_it() < max_t){
                    is_shadow = true;
                } 
            }
        }

        if(is_shadow){
            return Rgb();
        } else {
            return Rgb(1,1,1);
        }
    }

    Intersection closest_intersection;
    int materialId;
    double smallest_it;

    if (using_bvh) {
        closest_intersection = bvh_root->intersect(ray, DBL_MAX, surfaces, using_bbox, render_bbox);
        smallest_it = closest_intersection.get_smaller_it();
        materialId = closest_intersection.materialId;
    } else {
        smallest_it = DBL_MAX;
        materialId = 0; 
        
        for(int i=0; i<surfaces.size(); i++){
            Surface *s = surfaces[i];

            Intersection current_i = s->intersect(ray, using_bbox, render_bbox);
            if(current_i.does_intersect 
                    && current_i.intersection_t1 > min_t
                    && current_i.intersection_t1 < max_t){
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
    }

    if(!closest_intersection.does_intersect){
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

        Rgb shadow_rgb = calculateRgb(shadow_ray, 0.0001, distance_to_light, 1, ambient_light, bvh_root, surfaces, lights, materials, using_bbox, render_bbox, using_bvh);

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
                calculateRgb(reflective_ray, 0.0001, DBL_MAX, recurse_limit-1, ambient_light, bvh_root, surfaces, lights, materials, using_bbox, render_bbox, using_bvh) );
        }
    }

    // add ambient
    if (ray.type == "PRIMARY"){
        color += ( (materials[materialId]->diffuse_c * ambient_light.rgb) * 0.05 );
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






