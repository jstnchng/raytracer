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
	bool using_bbox = true;
	bool render_bbox = false;
	bool using_bvh = true;

	if (ac != 5) {
        std::cout << "usage: hw1.6 scenefile outputfilename num_primary_rays num_shadow_rays" << std::endl;
    }

    int p_samples = av[3][0] - '0';
    int s_samples = av[4][0] - '0';

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

   	cam.renderScene(surfaces, lights, materials, ambient_light, using_bbox, render_bbox, using_bvh, p_samples, s_samples);
	cout << "writing" << endl;
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
