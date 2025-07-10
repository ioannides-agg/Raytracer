#ifndef HITTABLE_H
#define HITTABLE_H

#include "../ray.h"
#include "../math.h"
#include "../interval.h"

struct hit_record {
    point3f point;
    vec3f normal;
    double t;
    bool front;

    void set_normal(const Ray& r, const vec3f& outward_normal) {
        front = dot(r.direction(), outward_normal) < 0;
        normal = front ? outward_normal : -outward_normal;
    }

};

class hittable_object {
    public:
      virtual ~hittable_object() = default;
      virtual bool hit(const Ray& r, hit_record& hit_data, interval bounds) const = 0;
};

#endif /* HITTABLE_H */