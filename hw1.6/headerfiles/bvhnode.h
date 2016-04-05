#ifndef __BVHNODE_H__
#define __BVHNODE_H__

#include <vector>

#include "bbox.h"
#include "point.h"
#include "intersection.h"
#include "ray.h"
#include "surface.h"

class BVHNode {
	public:
		BBox bbox;
		BVHNode * left;
		BVHNode * right;
		double scale;
		bool is_leaf;

	public:
		BVHNode();
		BVHNode(BBox &bbox, BVHNode* left, BVHNode* right);

		Intersection intersect(Ray &ray, double closest_t, std::vector< Surface * > &surfaces, bool using_bbox, bool render_bbox);
};

#endif