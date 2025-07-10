#ifndef RAY_H
#define RAY_H

#include "vector.h"

using color = vec3f;

class Ray {
private:
  point3f orig;
  vec3f dir;

public:
  Ray(const point3f origin, const vec3f direction)
      : orig(origin), dir(direction) {}

  // return immutable references of the ray's components
  const point3f &origin() const { return orig; }
  const vec3f &direction() const { return dir; }

  point3f at(auto t) const { return orig + dir * t; }
};

#endif /*RAY_H*/