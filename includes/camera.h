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
  const point3f camera_pos = point3f(0.0f, 0.0f, 0.0f);
  const float fov = rad(90);
  const int width = 1024;
  const int height = 768;
  const int samples_per_pixel = 100;
  const int max_depth = 50;

  void render(const hittable_object &world) {
    for (size_t i = 0; i < height; i++) {
      std::clog << "\rLines Remaining: " << height - i << " " << std::flush;
      for (size_t j = 0; j < width; j++) {
        color pixel_color(0.0f, 0.0f, 0.0f);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          float u = (j + random_float() - 0.5f) / float(width);
          float v = (i + random_float() - 0.5f) / float(height);

          float x = (2 * u - 1) * tan(fov / 2.0f) * aspect_ratio;
          float y = -(2 * v - 1) * tan(fov / 2.0f);

          point3f pixel_sample(x, y, 0);
          vec3f direction = vec3f(pixel_sample[0], pixel_sample[1], -1.0f);
          Ray ray = Ray(camera_pos, direction);
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