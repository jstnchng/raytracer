#ifndef __RGB_H__
#define __RGB_H__

class Rgb{
	public:
		double r, g, b;

	public:
		Rgb(){};
		Rgb(double re, double gr, double bl);

		void print();
		Rgb operator- (const Rgb rgb) const;
		Rgb operator+ (const Rgb rgb) const;
		Rgb operator* (const Rgb rgb) const;
		Rgb operator* (double scale);
};

#endif