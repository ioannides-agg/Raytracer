#ifndef SPHERE_H
#define SPHERE_H

#include "../math.h"
#include "../ray.h"
#include "hittable.h"

class Sphere : public hittable_object {
    private:
      point3f center;
      float radius;
    public:
      Sphere(const point3f& c, const float& r) : center(c), radius(std::fmax(0,r)) {}

      //in order for the ray to draw the sphere we will need every point on the 
      //surface of the sphere.
      bool hit(const Ray& r, hit_record& hit_data, float min, float max) const override {
        vec3f cq = center - r.origin();
        float a = r.direction().length_squared();
        float h = dot(r.direction(), cq);
        float c = cq.length_squared() - radius * radius;

        float discriminant = h*h - a*c;
        if(discriminant < 0) return false;

        float sqrtDiscriminant = std::sqrt(discriminant);
        float root = (h - sqrtDiscriminant) / a;

        if (root <= min || root >= max){
          root = (h + sqrtDiscriminant) / a;
          if (root <= min || root >= max) {
            return false;
          }
        }

        hit_data.t = root;
        hit_data.point = r.at(root);
        vec3f normal = (hit_data.point - center) / radius;
        hit_data.set_normal(r, normal);

        return true;
      }

};

#endif /*SPHERE_H*/