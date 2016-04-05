#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "camera.h"
#include "surface.h"
#include "light.h"

using namespace std;

//
// Basic parser for the scene files:
//
class Parser {
public:
    virtual void parse( const char *file, std::vector< Surface * > &surfaceVector, P_Light &light, Camera &cam);
};

#endif