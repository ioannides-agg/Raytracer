#ifndef HITTABLE_LIST_H
#define HITTBALE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

class hittable_list : public hittable_object {
    public:
      std::vector<std::shared_ptr<hittable_object>> objects;

      hittable_list() {}
      hittable_list(std::shared_ptr<hittable_object> obj) { add(obj); }

      void clear() { objects.clear(); }

      void add(std::shared_ptr<hittable_object> obj) { objects.push_back(obj); }

      bool hit(const Ray& r, hit_record& hit_data, float min, float max) const override {
          hit_record temp_hit;
          bool hit_anything;
          auto closest_object = max;

          for(const auto& obj : objects) {
              if (obj -> hit(r, temp_hit, min, closest_object)) {
                  hit_anything = true;
                  closest_object = temp_hit.t;
                  hit_data = temp_hit;

              }
          }

          return hit_anything;
      }

};

#endif /*HITTABLE_LIST_H*/