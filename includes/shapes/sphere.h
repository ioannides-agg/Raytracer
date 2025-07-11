#ifndef SPHERE_H
#define SPHERE_H

#include "../material.h"
#include "../math.h"
#include "../ray.h"
#include "hittable.h"

class Sphere : public hittable_object {
private:
  point3f center;
  float radius;
  std::shared_ptr<Material> mat_ptr; // Pointer to the material of the sphere

public:
  Sphere(const point3f &c, const float &r, std::shared_ptr<Material> material)
      : center(c), radius(std::fmax(0, r)), mat_ptr(material) {}

  // in order for the ray to draw the sphere we will need every point on the
  // surface of the sphere.
  bool hit(const Ray &r, hit_record &hit_data, interval bounds) const override {
    vec3f cq = center - r.origin();
    float a = r.direction().length_squared();
    float h = dot(r.direction(), cq);
    float c = cq.length_squared() - radius * radius;

    float discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    float sqrtDiscriminant = std::sqrt(discriminant);
    float root = (h - sqrtDiscriminant) / a;

    if (!bounds.surrounds(root)) {
      root = (h + sqrtDiscriminant) / a;
      if (!bounds.surrounds(root)) {
        return false;
      }
    }

    hit_data.t = root;
    hit_data.point = r.at(root);
    vec3f normal = (hit_data.point - center) / radius;
    hit_data.set_normal(r, normal);
    hit_data.mat_ptr = mat_ptr;

    return true;
  }
};

#endif /*SPHERE_H*/