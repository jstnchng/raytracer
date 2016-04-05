#include <assert.h>
#include <float.h>

#include "bbox.h"

BBox::BBox(){
	min = Point(0,0,0);
	max = Point(0,0,0);
    surface_index = -1;
}

BBox::BBox(Point &min, Point &max, int &surface_index){
    this->min = min;
    this->max = max;
    this->surface_index = surface_index;
}

void BBox::init(Point &min, Point &max){
    this->min = min;
    this->max = max;
}

void BBox::print(){
    std::cout << "bounding box: " << std::endl;
    std::cout << "	min: " << std::endl;
    min.print();
    std::cout << "	max: " << std::endl;
    max.print();
    std::cout << "  surface_index: " << surface_index << std::endl;
}

Intersection BBox::intersect(Ray &ray, int materialId){
	if(ray.dir[0] == -0){ 
		ray.dir.x = +0; 
	} if(ray.dir[1] == -0){ 
		ray.dir.y = +0;
	} if(ray.dir[2] == -0){ 
		ray.dir.z = +0; 
	}

	// double t_x_min = 0.0, t_x_max = 0.0; 
 //    double t_y_min = 0.0, t_y_max = 0.0;
 //    double t_z_min = 0.0, t_z_max = 0.0;

 //    if(ray.dir[0] == 0 && min[0] - ray.origin[0] >= 0){
 //        t_x_min = DBL_MAX;
 //    } else if (ray.dir[0] == 0 && min[0] - ray.origin[0] < 0){
 //        t_x_min = -DBL_MAX;
 //    } else {
 //        t_x_min = (min[0] - ray.origin[0]) / ray.dir[0];
 //    }
 //    if(ray.dir[0] == 0 && max[0] - ray.origin[0] >= 0){
 //        t_x_max = DBL_MAX;
 //    } else if (ray.dir[0] == 0 && max[0] - ray.origin[0] < 0){
 //        t_x_max = -DBL_MAX;
 //    } else {
 //        t_x_max = (max[0] - ray.origin[0]) / ray.dir[0];
 //    }

 //    if(ray.dir[1] == 0 && min[1] - ray.origin[1] >= 0){
 //        t_x_min = DBL_MAX;
 //    } else if (ray.dir[1] == 0 && min[1] - ray.origin[1] < 0){
 //        t_x_min = -DBL_MAX;
 //    } else {
 //        t_x_min = (min[1] - ray.origin[1]) / ray.dir[1];
 //    }
 //    if(ray.dir[1] == 0 && max[1] - ray.origin[1] >= 0){
 //        t_x_max = DBL_MAX;
 //    } else if (ray.dir[1] == 0 && max[1] - ray.origin[1] < 0){
 //        t_x_max = -DBL_MAX;
 //    } else {
 //        t_x_max = (max[1] - ray.origin[1]) / ray.dir[1];
 //    }

 //    if(ray.dir[2] == 0 && min[2] - ray.origin[2] >= 0){
 //        t_x_min = DBL_MAX;
 //    } else if (ray.dir[2] == 0 && min[2] - ray.origin[2] < 0){
 //        t_x_min = -DBL_MAX;
 //    } else {
 //        t_x_min = (min[2] - ray.origin[2]) / ray.dir[2];
 //    }
 //    if(ray.dir[2] == 0 && max[2] - ray.origin[2] >= 0){
 //        t_x_max = DBL_MAX;
 //    } else if (ray.dir[2] == 0 && max[2] - ray.origin[2] < 0){
 //        t_x_max = -DBL_MAX;
 //    } else {
 //        t_x_max = (max[2] - ray.origin[2]) / ray.dir[2];
 //    }

    double t_x_min = (min[0] - ray.origin[0]) / ray.dir[0];
    double t_x_max = (max[0] - ray.origin[0]) / ray.dir[0];
    double t_y_min = (min[1] - ray.origin[1]) / ray.dir[1];
    double t_y_max = (max[1] - ray.origin[1]) / ray.dir[1];
    double t_z_min = (min[2] - ray.origin[2]) / ray.dir[2];
    double t_z_max = (max[2] - ray.origin[2]) / ray.dir[2];

    double temp;
    if( t_x_min > t_x_max ){
    	temp = t_x_min;
        t_x_min = t_x_max;
        t_x_max = temp; 
    }

    if ( t_y_min > t_y_max ){
        temp = t_y_min;
        t_y_min = t_y_max;
        t_y_max = temp;
    }

    if ( t_z_min > t_z_max ){
        temp = t_z_min;
        t_z_min = t_z_max;
        t_z_max = temp;
    }

    // std::cout << t_x_min << " " << t_x_max << std::endl;
    if(t_x_min != t_x_min && t_x_max != t_x_max){
        std::cout << t_x_min << " " << t_x_max << std::endl;
        std::cout << (min[0] - ray.origin[0]) << std::endl;
        std::cout << ray.dir[0] << std::endl;
    }
    assert( t_x_min <= t_x_max );
    assert( t_y_min <= t_y_max );
    assert( t_z_min <= t_z_max );

    double min_t = -DBL_MAX;
    double max_t = DBL_MAX;

    if (t_x_min > min_t){
    	min_t = t_x_min;
    }
    if (t_x_max < max_t){
        max_t = t_x_max;
    }
    if (min_t > max_t){
        return Intersection();
    }

    if (t_y_min > min_t){
        min_t = t_y_min;
    }
    if (t_y_max < max_t){
        max_t = t_y_max;
    }
    if (min_t > max_t){
        return Intersection();
    }

    if (t_z_min > min_t){
        min_t = t_z_min;
    }
    if (t_z_max < max_t){
        max_t = t_z_max;
    }
    if (min_t > max_t){
        return Intersection();
    }

    Point intersection_pt1 = ray.evaluate(min_t);

    Vector normal;
    double min_d = 0.0001;

    double temp_x_min = intersection_pt1[0] - min[0];
    double temp_x_max = intersection_pt1[0] - max[0];
    double temp_y_min = intersection_pt1[1] - min[1];
    double temp_y_max = intersection_pt1[1] - max[1];
    double temp_z_min = intersection_pt1[2] - min[2];
    double temp_z_max = intersection_pt1[2] - max[2];

    if ( temp_x_min > -min_d && temp_x_min < min_d ){
        normal = Vector(-1 , 0 , 0);
    } else if ( temp_x_max > -min_d && temp_x_max < min_d ){
        normal = Vector(1 , 0 , 0);
    } else if ( temp_y_min > -min_d && temp_y_min < min_d ){
        normal = Vector(0 , -1 , 0);
    } else if ( temp_y_max > -min_d && temp_y_max < min_d ){
        normal = Vector(0 , 1 , 0);
    } else if ( temp_z_min > -min_d && temp_z_min < min_d ){
        normal = Vector(0 , 0 , -1);
    } else if ( temp_z_max > -min_d && temp_z_max < min_d ){
        normal = Vector(0 , 0 , 1);
    }

    return Intersection(true, min_t, max_t, intersection_pt1, intersection_pt1, normal, materialId);
}

Point BBox::get_centroid(){
    return Point( (min[0]+max[0])/2, (min[1]+max[1])/2, (min[2]+max[2])/2 );
}


