#include "config.h"

int main() {
  // create camera
  Camera cam;

  // objects to render
  hittable_list world;
  world.add(std::make_shared<Sphere>(point3f(0.0f, 0.0f, -1.0f), 0.5f));
  world.add(std::make_shared<Sphere>(point3f(0.0f, -100.5f, -1.0f), 100.0f));

  cam.render(world);

  return 0;
}