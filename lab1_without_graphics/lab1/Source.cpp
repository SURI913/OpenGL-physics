
#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath> 

#include "core.h"

int main()
{
	cyclone::Vector3 a(1, 2, -1);
	cyclone::Vector3 b(3, 0, 2);
	cyclone::Vector3 c = a.cross(b);
	if (c.magnitude() != 0) { //외적의 길이가 0이 아니어야 함
		c.normalise(); //길이 = 1
		b = c.cross(a);
	}

	std::cout << a.toString() << '\n' << b.toString() << '\n' << c.toString() << '\n';
	return 0;
}