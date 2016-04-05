#include "light.h"

using namespace std;

Light::Light(double r, double g, double b){
	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	type = '\0';
}

Vector Light::getLightDir (Point &intersectionPt) {
    std::cout << "error: Light::getLightDir should not be called - it's virtual!"<< std::endl;
    
    return Vector();
}

double Light::getDistance (Point &intersectionPt) {
    std::cout << "error: Light::getDistance should not be called - it's virtual!"<< std::endl;
    
    return 0.0;
}

