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
	P_Light light;

	Parser parser;
	parser.parse(av[1], surfaces, light, cam);
	assert (surfaces.size () != 0);

	cam.renderScene(surfaces, light);
	cam.writeImage(av[2]);
	
	return 0;	
}

