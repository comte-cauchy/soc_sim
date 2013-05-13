#ifndef VECT2D_
#define VECT2D_

struct vect2d {

	double x;
	double y;

	vect2d():x(0),y(0){};

	vect2d operator+(const vect2d&) const;
	vect2d operator-(const vect2d&) const;
	vect2d operator*(const double&) const;
	bool operator==(const vect2d&) const;
};

#endif //Vect2D_
