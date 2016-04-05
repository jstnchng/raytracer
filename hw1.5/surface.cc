#include "surface.h"

Intersection Surface::intersect (Ray &r, bool using_bbox, bool render_bbox) {
    std::cout << "error: surface::intersect should not be called - it's virtual!"<< std::endl;
    
    return Intersection();
}