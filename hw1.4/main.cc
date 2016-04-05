#include "main.h"

void
writeRgba (const char fileName[],
           const Rgba *pixels,
           int width,
           int height)
{
    RgbaOutputFile file (fileName, width, height, WRITE_RGBA);
    file.setFrameBuffer (pixels, 1, width);
    file.writePixels (height);
}

int main(int ac, char **av) {
	if (ac != 3) {
        // error condition: 
        std::cout << "usage: hw1.2 scenefile outputfilename" << std::endl;
    }

	Camera cam;
	std::vector<Surface * > surfaces;
	std::vector< Material * > materials;
	std::vector< Light * > lights;
	AmbientLight ambient_light;

	Material* default_material = new Material();
    materials.push_back (default_material);

	Parser parser;
	parser.parse(av[1], surfaces, lights, materials, ambient_light, cam);
	assert (surfaces.size () != 0);
    
    std:: cout << "read in: " << surfaces.size () << " surfaces, " << 
    lights.size () << " lights, " << 
    materials.size () - 1 << " materials." 
    << std::endl;

	cam.renderScene(surfaces, lights, materials, ambient_light);
	cam.writeImage(av[2]);

	for(int i=0; i < surfaces.size(); i++){
		Surface *surf = surfaces[i];
		delete(surf);
	}
	surfaces.clear();

	for(int i=0; i < materials.size(); i++){
		Material *mat = materials[i];
		delete(mat);
	}
	materials.clear();

	for(int i=0; i < lights.size(); i++){
		Light *light = lights[i];
		delete(light);
	}
	lights.clear();
	
	return 0;	
}
