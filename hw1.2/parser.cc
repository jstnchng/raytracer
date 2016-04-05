
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "parser.h"
#include "main.h"

using namespace std;

void Parser::parse(
    const char *file,
    std::vector< Surface * > &surfaceVector,
    P_Light &light,
    Camera &cam) 
{
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    int num_cams = 0; // keep track of how many cameras we read in

    Material lastMaterialLoaded;
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        Surface *thisSurface = 0;

        cmd="";
        
        istringstream iss(buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='/' or cmd.empty()) {
            continue;
        } 
        else if (cmd=="s") {
            // Sphere:
            
            // read in the parameters:
            Point pos; 
            double r;
            iss >> pos >> r;
            
            // construct it:
            // at the end of this loop, we put any newly-constructed surfaces
            // into the surfaceVector.
            // pos.print();

            thisSurface = new Sphere(pos, r, lastMaterialLoaded);
        } 
        else if (cmd=="t") {
            // Triangle
            
            // read in the parameters:
            Point pa,pb,pc;
            iss >> pa >> pb >> pc;
            
            // construct it:
//            triangle(a,b,c);
        } 
        else if (cmd=="p") {
            // Plane
            
            // read in the parameters:
            Vector n; 
            double d;
            iss >> n >> d;
            
            // construct it:
           thisSurface = new Plane(n, d, lastMaterialLoaded);
        } 
        else if (cmd=="c") {
            // Camera:
            ++num_cams; // keep track of how many we read in
 
            
            // read in the parameters:
            Point pos; Vector dir; 
            double d,iw,ih; 
            int pw,ph;
            iss >> pos >> dir >> d >> iw >> ih >> pw >> ph;
            
            // construct it:
            // cout << "eye: " << pos.x << ", " << pos.y << ", " << pos.z << endl; 
            cam.init (pos,dir,d,iw,ih,pw,ph);
        } 
        else if (cmd=="l") {
            iss >> cmd;
            if (cmd=="p") {
                double x,y,z;
                double r,g,b;
                iss >> x >> y >> z >> r >> g >> b;
                Point p (x,y,z);
                light = P_Light (r,g,b,p);
                // light.rgb.print();
            } 
            else if (cmd=="d") {
                Vector dir,rgb;
                iss >> dir >> rgb;
//                directionalLight(dir,rgb);
            } 
            else if (cmd=="a") {
                Vector rgb;
                iss >> rgb;
//                ambientLight(rgb);
            } 
            else {
                cout << "Parser error: invalid light at line " << line << endl;
            }
        } 
        else if (cmd=="m") {
            // Material:
            
            // read in the parameters:
            double dr, dg, db;
            double sr, sg, sb;
            double ir, ig, ib;
            double r;
            iss >> dr >> dg >> db >> sr >> sg >> sb >> r >> ir >> ig >> ib;
            
            // construct it:
            lastMaterialLoaded.setMaterial(dr, dg, db, sr, sg, sb, r, ir, ig, ib);
            // lastMaterialLoaded.print();
        } 
        else {
            std::cerr << "Parser error: invalid command at line " << line << endl;
        }
        
        // if we found a surface, add it to the list of surfaces:
        if (thisSurface)
            surfaceVector.push_back (thisSurface);
    }
    
    in.close();
    
    // make sure we read in 1 camera, no more no less 8).
    if (num_cams != 1) {
        std::cerr << "scene file error: exactly ONE camera must be defined." << endl;
    }
}
