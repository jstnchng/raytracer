#ifndef PARSE_H
#define PARSE_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "camera.h"
#include "surface.h"
#include "light.h"
#include "ambientlight.h"

using namespace std;

//
// Basic parser for the scene files:
//
class Parser {
public:
    virtual void parse( const char *file, 
    					std::vector< Surface * > &surfaceVector, 
    					std::vector< Light * > &lightVector,
    					std::vector< Material * > &matVector,
    					AmbientLight &ambient_light,
    					Camera &cam);
    void read_wavefront_file (	const char *file,
    							std::vector< int > &tris,
    							std::vector< float > &verts);

};

#endif
