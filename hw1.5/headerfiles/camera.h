#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <vector>

#include "point.h"
#include "vector.h"
#include "ray.h"
#include "surface.h"
#include "material.h"
#include "intersection.h"
#include "light.h"
#include "rgb.h"
#include "ambientlight.h"
#include "bbox.h"
#include "bvhnode.h"

using namespace Imf;
using namespace Imath;

class Camera {
	public:
		Point eye;

		float focal_length; // focal length

		Vector u;
		Vector v;
		Vector w;

		int pixels_width; // pixels width iw used to be nx
		int pixels_height; // pixels height ih used to be ny

		float image_width, image_height; //image width & height pw ph

		Array2D<Rgba> pixelBuffer;

	public: 
		Camera(){};

		void init(Point &eye, Vector &dir, float d, float iw, float ih, int pw, int ph);

		void print();

		Ray generateRay (const int i, const int j);

		BVHNode* build_bvh_tree(std::vector< BBox * > &bboxes, int axis);
		
		void renderScene (std::vector< Surface * > &surfaces, 
			std::vector< Light * > &lights, 
			std::vector< Material * > &materials, 
			AmbientLight &ambient_light,
			bool using_bbox, bool render_bbox, bool using_bvh);

		void writeImage (const char* sceneFile);

		Rgb calculateRgb(Ray &ray, double min_t, double max_t, int recurse_limit, 
			AmbientLight &ambient_light, BVHNode * bvh_root,
        	std::vector< Surface * > &surfaces,
        	std::vector< Light * > &lights,
        	std::vector< Material * > &materials,
        	bool using_bbox, bool render_bbox, bool using_bvh);

		void setPixel (int pix_x, int pix_y, Rgb &rgb) {
	        Rgba &px = pixelBuffer[pix_y][pix_x];
	        px.r = rgb.r;
	        px.g = rgb.g;
	        px.b = rgb.b;
	        px.a = 1.0;
    	}
};

#endif

