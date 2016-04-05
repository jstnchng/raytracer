
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
    std::vector< Light * > &lightVector,
    std::vector< Material * > &matVector,
    AmbientLight &ambient_light,
    Camera &cam) 
{
    
    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    int num_cams = 0; // keep track of how many cameras we read in

    int currentMaterialIndex = 0;

    std::vector< int > tris;
    std::vector< float > verts;
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
        
        Surface *thisSurface = 0;
        Light *thisLight = 0;
        Material *thisMat = 0;
        Surface *thisTriangle = 0;

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

            thisSurface = new Sphere(pos, r);
        } 
        else if (cmd=="t") {
            // Triangle
            
            // read in the parameters:
            Point pa,pb,pc;
            iss >> pa >> pb >> pc;
            
            // construct it:
            thisSurface = new Triangle(pa, pb, pc);
            // thisSurface->print();
        } 
        else if (cmd=="p") {
            // Plane
            
            // read in the parameters:
            Vector n; 
            double d;
            iss >> n >> d;
            
            // construct it:
           thisSurface = new Plane(n, d);
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
                thisLight = new P_Light (r,g,b,p);
            } 
            else if (cmd=="d") {
                double x,y,z;
                double r,g,b;
                iss >> x >> y >> z >> r >> g >> b;
                Vector d (x,y,z);
                thisLight = new D_Light (r,g,b,d);
            } 
            else if (cmd=="a") {
                double r,g,b;
                iss >> r >> g >> b;
                
                ambient_light.init(r,g,b);
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
            
            thisMat = new Material (dr, dg, db, sr, sg, sb, r, ir, ig, ib);

            ++currentMaterialIndex;
        } 
        else if (cmd=="w"){
            string f;
            iss >> f;
            const char *file = f.c_str();

            read_wavefront_file(file, tris, verts);
            Point a, b, c;

            for(int i=0; i<tris.size()/3; i++){
                a.init( verts[3*tris[3*i]], verts[3*tris[3*i]+1], verts[3*tris[3*i]+2]);
                b.init( verts[3*tris[3*i+1]], verts[3*tris[3*i+1]+1], verts[3*tris[3*i+1]+2]);
                c.init( verts[3*tris[3*i+2]], verts[3*tris[3*i+2]+1], verts[3*tris[3*i+2]+2]);

                thisTriangle = new Triangle(a, b, c);
                thisTriangle->set_bbox();
                surfaceVector.push_back(thisTriangle);
                thisTriangle->setMaterialIndex (currentMaterialIndex);
            }
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << endl;
        }
        
        // if we found a surface, add it to the list of surfaces:
        if (thisSurface){
            thisSurface->set_bbox();
            surfaceVector.push_back (thisSurface);
            thisSurface->setMaterialIndex (currentMaterialIndex);
        }
        if (thisLight){
            lightVector.push_back (thisLight);
        }
        if (thisMat){
            matVector.push_back (thisMat);
        }
    }
    
    in.close();
    
    // make sure we read in 1 camera, no more no less 8).
    if (num_cams != 1) {
        std::cerr << "scene file error: exactly ONE camera must be defined." << endl;
    }
}

// Given the name of a wavefront (OBJ) file that consists JUST of
// vertices, triangles, and comments, read it into the tris and verts
// vectors.
//
// tris is a vector of ints that is 3*n long, where n is the number of
// triangles. The ith triangle has vertex indexes 3*i, 3*i+1, and 3*i+2.
//
// The ith triangle has vertices verts[3*i], verts[3*i+1], and verts[3*i+2],
// given in counterclockwise order with respect to the surface normal
//
void Parser::read_wavefront_file (
    const char *file,
    std::vector< int > &tris,
    std::vector< float > &verts)
{
    
    // clear out the tris and verts vectors:
    tris.clear ();
    verts.clear ();

    ifstream in(file);
    char buffer[1025];
    string cmd;
    
    
    for (int line=1; in.good(); line++) {
        in.getline(buffer,1024);
        buffer[in.gcount()]=0;
                
        cmd="";
        
        istringstream iss (buffer);
        
        iss >> cmd;
        
        if (cmd[0]=='#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        } 
        else if (cmd=="v") {
            // got a vertex:
            
            // read in the parameters:
            double pa, pb, pc;
            iss >> pa >> pb >> pc;
 
            verts.push_back (pa);
            verts.push_back (pb);
            verts.push_back (pc);
         } 
        else if (cmd=="f") {
            // got a face (triangle)
            
            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;
            
            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back (i-1);
            tris.push_back (j-1);
            tris.push_back (k-1);
        } 
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }
        
     }
    
    in.close();
    
    std::cout << "found this many tris, verts: " << tris.size () / 3.0 << "  " 
              << verts.size () / 3.0 << std::endl;
}



