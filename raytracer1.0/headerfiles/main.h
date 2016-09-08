#include <ImfRgbaFile.h>
#include <ImfStringAttribute.h>
#include <ImfMatrixAttribute.h>
#include <ImfArray.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <assert.h>

#include "point.h"
#include "vector.h"
#include "camera.h"
#include "ray.h"
#include "parser.h"
#include "sphere.h"
#include "surface.h"
#include "plane.h"
#include "material.h"
#include "light.h"
#include "ambientlight.h"
#include "dirlight.h"
#include "arealight.h"
#include "pointlight.h"
#include "triangle.h"

using namespace std;
using namespace Imf;
using namespace Imath;