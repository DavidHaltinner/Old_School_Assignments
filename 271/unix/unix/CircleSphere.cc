#include <iostream.h>
#include <math.h>
#include "CircleSphere.h"

int main ()
{
	double radius_of_both, area_of_circle, volume_of_sphere;
	cout << "Enter a radius to use for both a circle"
	     << " and a sphere (in inches): ";
	cin >> radius_of_both;
	area_of_circle=area(radius_of_both);
	volume_of_sphere=volume(radius_of_both);
	cout << "Radius = " << radius_of_both << " inches.\n"
	     << "Area of circle = " << area_of_circle << " square inches.\n"
	     << "Volume of sphere = " << volume_of_sphere << " cubic inches.\n";
	return 0;
}	