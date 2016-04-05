#include "hw0.h"

void
writeRgba (const char fileName[],
			const Rgba *pixels,
			int width,
			int height,
			const Box2i &dataWindow)
{
	Box2i displayWindow (V2i (width/3, height/3), V2i (2*width/3-1, 2*height/3-1));

	RgbaOutputFile file (fileName, displayWindow, dataWindow, WRITE_RGBA);

	file.setFrameBuffer (pixels, 1, width);

	file.writePixels (dataWindow.max.y - dataWindow.min.y + 1);
}

void
readRgba (const char fileName[],
          Array2D<Rgba> &pixels,
          int &width,
          int &height)
{
    //
    // Read an RGBA image using class RgbaInputFile:
    //
    //	- open the file
    //	- allocate memory for the pixels
    //	- describe the memory layout of the pixels
    //	- read the pixels from the file
    //

    RgbaInputFile file (fileName);
    Box2i dw = file.dataWindow();
    
    width  = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase (height, width);
    
    file.setFrameBuffer (&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels (dw.min.y, dw.max.y);
}

int
main (int argc, char *argv[])
{
    try
    {
        
        cout << "reading " << argv[1] << endl;
        
        int w, h;
        Array2D<Rgba> p;
        
        ifstream file(argv[1]);
		if (!file)
		{
		    cout << "file invalid" << endl;
		    exit(0);
		}

        readRgba (argv[1], p, w, h);
        
        cout << "image width height is: " << w << "  " << h << endl;

        // in greyscale first
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                Rgba &px = p[y][x];  // get the pixel we are interested in
                
                double l = 0.2126*px.r + 0.7152*px.g + 0.0722*px.b;

                px.r = l;
                px.g = l;
                px.b = l;
                px.a = 1;
            }
        }

        cout << "writing output image" << endl;

        writeRgba ("hw0.exr", &p[0][0], w, h,
        			Box2i( V2i(w/3,h/3), V2i(2*w/3-1, 2*h/3-1) ));

        cout << "new image width height is: " << w/3 << "  " << h/3 << endl;
        
        cout << "done." << endl;

    }

    catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return 1;
    }
    
    return 0;
}

