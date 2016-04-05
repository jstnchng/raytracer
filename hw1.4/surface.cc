#include "surface.h"

Intersection Surface::intersect ( Ray &r) 
{
    std::cout << "error: surface::intersect should not be called - it's virtual!"<< std::endl;
    
    return Intersection();
}
