#include "config.h"

int main() {
  // create camera
  Camera cam;

  // create materials
  auto material_ground = std::make_shared<Lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<Lambertian>(color(0.1, 0.2, 0.5));
  auto material_left = std::make_shared<Metal>(color(0.8, 0.8, 0.8));
  auto material_right = std::make_shared<Metal>(color(0.8, 0.6, 0.2));

  // objects to render
  hittable_list world;
  world.add(std::make_shared<Sphere>(point3f(0.0f, -100.5f, -1.0f), 100.0f,
                                     material_ground));
  world.add(std::make_shared<Sphere>(point3f(0.0f, 0.0f, -1.2f), 0.5f,
                                     material_center));
  world.add(std::make_shared<Sphere>(point3f(-1.0f, 0.0f, -1.0f), 0.5f,
                                     material_left));
  world.add(std::make_shared<Sphere>(point3f(1.0f, 0.0f, -1.0f), 0.5f,
                                     material_right));

  cam.render(world);

  return 0;
}