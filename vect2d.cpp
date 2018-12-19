#include "vect2d.hpp"

vect2d vect2d::operator+(const vect2d& rhs) const
{
	vect2d coords=rhs;
	coords.x=x+rhs.x;
	coords.y=y+rhs.y;
	return coords;
}

vect2d vect2d::operator-(const vect2d& rhs) const
{
	vect2d coords;
	coords.x=x-rhs.x;
	coords.y=y-rhs.y;
	return coords;
}

vect2d vect2d::operator*(const double& m) const
{
	vect2d coords;
	coords.x=x*m;
	coords.y=y*m;
	return coords;
}

bool vect2d::operator==(const vect2d& rhs) const
{
	return x==rhs.x&&y==rhs.y;
}
