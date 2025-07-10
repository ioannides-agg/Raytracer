#ifndef MATH_H
#define MATH_H

#include "vector.h"
#include <cstdlib>

const double infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;

float rad(float degrees) { return degrees * pi / 180; }

float random_float() {
  // returns a random float in the range [0, 1)
  return std::rand() / (RAND_MAX + 1.0f);
}

float random_float(float min, float max) {
  // returns a random float in the range [min, max)
  return min + (max - min) * random_float();
}

#endif /*MATH_H*/