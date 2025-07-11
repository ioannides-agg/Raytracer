#ifndef MATH_H
#define MATH_H

#include "vector.h"
#include <cstdlib>

using color = vec3f;

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

vec3f random_vector() {
  return vec3f(random_float(), random_float(), random_float());
}

vec3f random_vector(float min, float max) {
  return vec3f(random_float(min, max), random_float(min, max),
               random_float(min, max));
}

inline vec3f random_unit_vector() {
  // Generates a random unit vector using spherical coordinates
  float phi = random_float(0, 2 * pi);
  float theta = acos(random_float(-1, 1));

  float x = sin(theta) * cos(phi);
  float y = sin(theta) * sin(phi);
  float z = cos(theta);

  return vec3f(x, y, z);
}

inline vec3f random_on_hemisphere(const vec3f &normal) {
  vec3f on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}

#endif /*MATH_H*/