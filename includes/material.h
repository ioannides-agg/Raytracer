#ifndef MATERIAL_H
#define MATERIAL_H

#include "math.h"
#include "ray.h"
#include "shapes/hittable.h"

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray $r, const hit_record &hit, color &attentuation,
                       Ray &scattered) const {
    return false;
  }
};

#endif /* MATERIAL_H */