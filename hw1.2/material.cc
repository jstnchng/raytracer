#include "material.h"

using namespace std;

Material::Material(){
	diffuse_c = Rgb (0,0,0);

	specular_c = Rgb (0,0,0);

	ideal_specular_c = Rgb (0,0,0);

	phong_exp = 0;
}

Material::Material(double dcr, double dcg, double dcb, double sr, double sg, double sb, double r, double ir, double ig, double ib){
	diffuse_c = Rgb (dcr,dcg,dcb);

	specular_c = Rgb (sr,sg,sb);

	ideal_specular_c = Rgb (ir,ig,ib);

	phong_exp = r;
}

Material::Material(Vector dc, Vector sc, double r, Vector isc){
	diffuse_c = Rgb (dc[0],dc[1],dc[2]);

	specular_c = Rgb (sc[0],sc[1],sc[2]);

	ideal_specular_c = Rgb (isc[0],isc[1],isc[2]);

	phong_exp = r;
}

void Material::setMaterial(double dcr, double dcg, double dcb, double sr, double sg, double sb, double r, double ir, double ig, double ib){
	diffuse_c = Rgb (dcr,dcg,dcb);

	specular_c = Rgb (sr,sg,sb);

	ideal_specular_c = Rgb (ir,ig,ib);

	phong_exp = r;
}

void Material::print(){
	cout << "material {" << endl;
	cout << " diffuse components " << diffuse_c.r << ", " << diffuse_c.g << ", " << diffuse_c.b << ">" << endl;
	cout << " specular components " << specular_c.r << ", " << specular_c.g << ", " << specular_c.b << ">" << endl;
	cout << " ideal specular components " << ideal_specular_c.r << ", " << ideal_specular_c.g << ", " << ideal_specular_c.b << ">" << endl;
	cout << " phong exponent <" << phong_exp << ">" << endl;
	cout << "}" << endl;
}