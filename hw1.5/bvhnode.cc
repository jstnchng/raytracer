#include "bvhnode.h"

BVHNode::BVHNode(){
	left = nullptr;
	right = nullptr;
	is_leaf = false;
	bbox = BBox();
}

BVHNode::BVHNode(BBox &bbox, BVHNode* left, BVHNode* right){
	this->bbox = bbox;
	this->left = left;
	this->right = right;
	is_leaf = false;
	scale = 0.00000001;
}

Intersection BVHNode::intersect(Ray &ray, double closest_t, std::vector< Surface * > &surfaces, bool using_bbox, bool render_bbox){
	double this_t;
	int materialId = -1;
	if(bbox.surface_index != -1){
		Surface *s = surfaces[bbox.surface_index];
    	materialId = s->materialIndex;
    }

    Intersection bbox_intersection = bbox.intersect(ray, materialId);
    if (!bbox_intersection.does_intersect){
        return bbox_intersection;
    } else {
        this_t = bbox_intersection.get_smaller_it();
    }

	if (this_t < closest_t){
		if (is_leaf){
            Surface *s = surfaces[bbox.surface_index];
            Intersection intersection = s->intersect(ray, using_bbox, render_bbox);
            if(intersection.does_intersect && intersection.get_smaller_it() > 0.0001){
            	return intersection;
            } else {
            	return Intersection();
            }
		} else {
			Intersection left_intersection, right_intersection;
			if(left != nullptr){
                left_intersection = left->intersect(ray, closest_t, surfaces, using_bbox, render_bbox);
            }
            if(right != nullptr){
                right_intersection = right->intersect(ray, closest_t, surfaces, using_bbox, render_bbox);
            }

            if (left_intersection.does_intersect == false && right_intersection.does_intersect == true){
                return right_intersection;
            }

            else if (left_intersection.does_intersect == true && right_intersection.does_intersect == false){
                return left_intersection;
            }

            else if (left_intersection.does_intersect == true && right_intersection.does_intersect == true){
                if (left_intersection.get_smaller_it() < right_intersection.get_smaller_it()){	
                    return left_intersection;
                }
                else {
                    return right_intersection;
                }
            }

            else {
                return Intersection();
            }
		}
	} else {
		return Intersection();
	}
}	




