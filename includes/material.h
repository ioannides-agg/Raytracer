#ifndef MATERIAL_H
#define MATERIAL_H

#include "math.h"
#include "ray.h"
#include "shapes/hittable.h"

vec3f reflect(const vec3f &v, const vec3f &n) { return v - 2 * dot(v, n) * n; }

vec3f refract(const vec3f &v, const vec3f &n, float etai_over_etat) {
  float cos_theta = std::fmin(dot(-v, n), 1.0f);
  vec3f r_out_perp = etai_over_etat * (v + cos_theta * n);
  vec3f r_out_parallel =
      -std::sqrt(std::fabs(1.0f - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}

float schlick(float cosine, float ref_idx) { // OHHHH HE THINK HE SCHLICK
  float r0 = (1 - ref_idx) / (1 + ref_idx);
  r0 *= r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

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
  float fuzziness; // Fuzziness factor for roughness

public:
  Metal(const color &a, float f) : albedo(a), fuzziness(f < 1.0f ? f : 1) {}

  bool scatter(const Ray &r, const hit_record &hit, color &attentuation,
               Ray &scattered) const override {
    vec3f reflected = reflect(r.direction(), hit.normal);

    vec3f fuzzed_reflection =
        reflected.normalized() + fuzziness * random_unit_vector();
    scattered = Ray(hit.point, fuzzed_reflection);
    attentuation = albedo;
    return dot(scattered.direction(), hit.normal) > 0;
  }
};

class Dielectric : public Material {
private:
  float ref_idx;

public:
  Dielectric(float ri) : ref_idx(ri) {}

  bool scatter(const Ray &r, const hit_record &hit, color &attentuation,
               Ray &scattered) const override {
    attentuation = color(1.0f, 1.0f, 1.0f); // White light
    float ri = hit.front ? (1.0f / ref_idx) : ref_idx;

    vec3f direction = r.direction();
    vec3f unit_direction = direction.normalized();
    float cos_theta = std::fmin(dot(-unit_direction, hit.normal), 1.0f);
    float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);
    vec3f refract_direction;

    if (ri * sin_theta > 1.0f || schlick(cos_theta, ri) > random_float()) {
      refract_direction = reflect(unit_direction, hit.normal);
    } else {
      refract_direction = refract(unit_direction, hit.normal, ri);
    }

    scattered = Ray(hit.point, refract_direction);
    return true;
  }
};
#endif /* MATERIAL_H */