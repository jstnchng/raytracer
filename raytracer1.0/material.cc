#include "material.h"

using namespace std;

Material::Material(){
	diffuse_c = Rgb (0.2, 0.3, 0.8);

	specular_c = Rgb (0.9, 0.9, 0.9);

	ideal_specular_c = Rgb (0., 0., 0.);

	phong_exp = .05;
}

Material::Material(double dcr, double dcg, double dcb, double sr, double sg, double sb, double r, double ir, double ig, double ib){
	diffuse_c = Rgb (dcr,dcg,dcb);

	specular_c = Rgb (sr,sg,sb);

	ideal_specular_c = Rgb (ir,ig,ib);

	phong_exp = r;
}

Material::Material(Vector &dc, Vector &sc, double r, Vector &isc){
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

Rgb Material::phongShading(Vector &v, Vector &light_dir, Rgb &light_rgb, Vector &normal){
	// Vector normal = intersection.normal;
	// Point ipt = intersection.get_closer_ipt();

	// Vector light_dir = light->getLightDir(ipt);
	// Rgb light_rgb = light->rgb;

	Rgb big_L;

	Rgb l_diffuse;
	double n_ld = normal.dotProduct(light_dir);
	n_ld = max(0.0, n_ld);

	Rgb kd_I = diffuse_c * light_rgb;
	l_diffuse = kd_I * n_ld;

	Rgb l_specular (0,0,0);
	Vector h = v + light_dir;

	if (h.length() > 0.){
		h.normalize();

		double n_h = normal.dotProduct(h);
		n_h = max(0.0, n_h);
		n_h = pow(n_h, phong_exp);

		Rgb ks_I = specular_c * light_rgb;
		l_specular = ks_I * n_h;
	}

	big_L = l_diffuse + l_specular;

	return big_L;
}
