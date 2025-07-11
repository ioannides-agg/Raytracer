#ifndef CAMERA_H
#define CAMERA_H

#include "../includes/PPM_image_writer.h"
#include "../includes/interval.h"
#include "material.h"
#include "math.h"
#include "ray.h"
#include "shapes/hittable.h"
#include <iostream>

color white = color(1.0f, 1.0f, 1.0f);
color blue = color(0.5f, 0.7f, 1.0f);
color red = color(1.0f, 0.0f, 0.0f);

class Camera {
public:
  point3f camera_pos = point3f(0.0f, 3.0f, 0.0f);
  point3f look_at = point3f(0.0f, 0.0f, -1.0f);
  float fov = rad(90);
  const int width = 1024;
  const int height = 768;
  const int samples_per_pixel = 10;
  const int max_depth = 50;

  void render(const hittable_object &world) {
    vec3f w = (camera_pos - look_at).normalized();
    vec3f u = cross(vec3f(0.0f, 1.0f, 0.0f), w).normalized();
    vec3f v = cross(w, u).normalized();

    float viewport_height =
        2.0f * tan(fov / 2.0f) *
        -1.0f; // negative because the camera looks towards negative z
    float viewport_width = 2.0f * tan(fov / 2.0f) * aspect_ratio;

    point3f lower_left_corner = camera_pos - (viewport_width / 2.0f) * u -
                                (viewport_height / 2.0f) * v - w;

    for (size_t i = 0; i < height; i++) {
      std::clog << "\rLines Remaining: " << height - i << " " << std::flush;
      for (size_t j = 0; j < width; j++) {
        color pixel_color(0.0f, 0.0f, 0.0f);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          float u_offset = (j + random_float() - 0.5f) / float(width);
          float v_offset = (i + random_float() - 0.5f) / float(height);

          vec3f direction = lower_left_corner + u_offset * viewport_width * u +
                            v_offset * viewport_height * v - camera_pos;

          Ray ray = Ray(camera_pos, direction.normalized());
          pixel_color += color_ray(ray, world, max_depth);
        }

        interval in(0.000f, 0.999f);
        pixel_color = pixel_color / samples_per_pixel;
        color pixel(in.clamp(linear_to_gamma(pixel_color[0])),
                    in.clamp(linear_to_gamma(pixel_color[1])),
                    in.clamp(linear_to_gamma(pixel_color[2])));

        framebuffer.push_back(pixel);
      }
    }

    PPM_image_writer("render.ppm", width, height, framebuffer);
  }

private:
  const float aspect_ratio = float(width) / float(height);
  std::vector<color> framebuffer;

  color color_ray(const Ray &r, const hittable_object &world, int depth) {
    if (depth <= 0) {
      return color(0.0f, 0.0f, 0.0f); // terminate recursion
    }

    hit_record hit;
    if (world.hit(r, hit, interval(0.001f, infinity))) {
      Ray scattered;
      color attentuation;
      if (hit.mat_ptr->scatter(r, hit, attentuation, scattered)) {
        return attentuation * color_ray(scattered, world, depth - 1);
      }
      return color(0.0f, 0.0f, 0.0f); // no scatter, return black
    }

    // background sky gradient
    vec3f dir = r.direction();
    float a = 0.5f * (dir.normalized()[1] + 1.0f);
    return (1.0f - a) * white + a * blue;
  }

  double linear_to_gamma(double linear_component) {
    if (linear_component > 0)
      return std::sqrt(linear_component);

    return 0;
  }
};
#endif /*CAMERA_H*/