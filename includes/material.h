#ifndef MATERIAL_H
#define MATERIAL_H

#include "math.h"
#include "ray.h"
#include "shapes/hittable.h"

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r, const hit_record &hit, color &attentuation,
                       Ray &scattered) const {
    return false;
  }
};

class Lambertian : public Material {
private:
  color albedo;

public:
  Lambertian(const color &a) : albedo(a) {}

  bool scatter(const Ray &r, const hit_record &hit, color &attentuation,
               Ray &scattered) const override {
    vec3f scatter_direction = hit.normal + random_unit_vector();

    if (vector_near_zero(scatter_direction)) {
      // If the scatter direction is near zero, we use the normal as the
      // direction
      scatter_direction = hit.normal;
    }

    scattered = Ray(hit.point, scatter_direction);
    attentuation = albedo;
    return true;
  }
};

class Metal : public Material {
private:
  color albedo;

public:
  Metal(const color &a) : albedo(a) {}

  bool scatter(const Ray &r, const hit_record &hit, color &attentuation,
               Ray &scattered) const override {
    vec3f reflected =
        r.direction() - 2 * dot(r.direction(), hit.normal) * hit.normal;
    scattered = Ray(hit.point, reflected);
    attentuation = albedo;
    return true;
  }
};
#endif /* MATERIAL_H */