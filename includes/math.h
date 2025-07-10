#ifndef MATH_H
#define MATH_H

#include "vector.h"

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

float rad(float degrees) { return degrees * pi / 180; }

#endif /*MATH_H*/