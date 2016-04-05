#include <iostream>
#include <fstream>

#include "main.h"

Camera cam;
std::vector<Surface> surfaces;
std::vector<Sphere> spheres;
Sphere sph;

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
	POVRayParser parser;
	parser.parse(av[1]);

	cam.print();
	int red_px = 0;
	int total_px = 0;
	int intersections = 0;

	ofstream myfile;
  	myfile.open ("output.txt");

	try {
		Array2D<Rgba> p (cam.ny, cam.nx) ;
		const char filename[] = "hw1.1.exr";

		// for(int i=0; i< cam.nx; i++){
			// for(int j=0; j<cam.ny; j++){
		for(int i=312; i<313; i++){
			for(int j=151; j<152; j++){
				double u = cam.width/2*-1 + cam.width*(i+0.5)/cam.nx;
				double v = cam.height/2 - cam.height*(j+0.5)/cam.ny;

				Vector dw = (cam.w).multiply(-1*cam.d);
				Vector uu = (cam.u).multiply(u);
				Vector vv = (cam.v).multiply(v);

				Vector temp = dw.add(uu);
				Vector dir = temp.add(vv);

		  		dir.normalize();

		  		Ray ray (cam.eye, dir);
		  		// cout << "Origin: " << "<" << ray.origin.x << ", " << ray.origin.y << ", " << ray.origin.z << ">" << endl;
				// cout << "Direction: " << "<" << ray.dir.x << ", " << ray.dir.y << ", " << ray.dir.z << ">" << endl;

		  		bool intersect = false;

		  		// int i = 0;
		  		// while(!intersect || i<spheres.size()){
		  		// 	if ( spheres.at(i).intersect(ray) >= 0 ){
		  		// 		intersect = true;
		  		// 		intersections++;
		  		// 	}
		  		// 	i++;
		  		// }

		  		for(int n=0; n<spheres.size(); n++){
		  			if ( spheres.at(n).intersect(ray) >= 0 ){
		  				std::cout << "intersecting discriminant " << spheres.at(n).intersect(ray) << std::endl;
		  				intersect = true;
		  				intersections++;
		  				myfile << i << ", " << j << std::endl;
		  			}
		  		}

		  		Rgba px;
		  		if(intersect == false){
		  			px.r = 0;
		  			px.g = 0;
		  			px.b = 0;
		  		} else {
		  			px.r = 1;
		  			px.g = 0;
		  			px.b = 0;
		  			red_px++;
		  		}
		  		px.a = 1;
		  		p[j][i] = px;

		  		total_px++;
			}
		}
		writeRgba(filename, &p[0][0], cam.nx, cam.ny);
	} catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }

    cout << "red pixels: " << red_px << endl;
    cout << "total pixels: " << total_px << endl;
    cout << "intersections: " << intersections << endl;
	
	return 0;	
}

