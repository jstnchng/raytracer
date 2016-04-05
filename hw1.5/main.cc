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
	bool using_bbox, render_bbox, using_bvh;

	if (ac != 4) {
        std::cout << "usage: hw1.2 scenefile outputfilename bboxflags" << std::endl;
    }

    if (ac==3){
    	using_bbox = true;
	    render_bbox = false;
	    using_bvh = true;
    } else { 
	    if(av[3][0] == '0'){
	    	using_bbox = false;
	    	render_bbox = false;
	    	using_bvh = false;
	    } else if (av[3][0] == '1'){
	    	using_bbox = true;
	    	render_bbox = true;
	    	using_bvh = false;
	    } else if (av[3][0] == '2'){
	    	using_bbox = true;
	    	render_bbox = true;
	    	using_bvh = true;
	    } else if (av[3][0] == '3'){
	    	using_bbox = true;
	    	render_bbox = false;
	    	using_bvh = true;
	    } else {
	    	std::cout << "usage: bboxflag supports 0,1,2,3 only" << std::endl;
	    }
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

	cam.renderScene(surfaces, lights, materials, ambient_light, using_bbox, render_bbox, using_bvh);
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
