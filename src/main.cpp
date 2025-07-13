#include "config.h"

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  hittable_list world;

  auto ground_material = std::make_shared<Lambertian>(color(0.5f, 0.5f, 0.5f));
  world.add(
      std::make_shared<Sphere>(point3f(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_float();
      point3f center(a + 0.9f * random_float(), 0.2f,
                     b + 0.9f * random_float());

      if ((center - point3f(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
        std::shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8f) {
          // diffuse
          auto albedo = random_vector() * random_vector();
          sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
        } else if (choose_mat < 0.95f) {
          // metal
          auto albedo = random_vector(0.5f, 1.0f);
          auto fuzz = random_float(0.0f, 0.5f);
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<Dielectric>(1.5f);
          world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<Dielectric>(1.5f);
  world.add(
      std::make_shared<Sphere>(point3f(0.0f, 1.0f, 0.0f), 1.0f, material1));

  auto material2 = std::make_shared<Lambertian>(color(0.4, 0.2, 0.1));
  world.add(
      std::make_shared<Sphere>(point3f(-4.0f, 1.0f, 0.0f), 1.0f, material2));

  auto material3 = std::make_shared<Metal>(color(0.7f, 0.6f, 0.5f), 0.0f);
  world.add(
      std::make_shared<Sphere>(point3f(4.0f, 1.0f, 0.0f), 1.0f, material3));

  Camera cam;

  cam.height = 1080;
  cam.width = 1920;
  cam.fov = rad(20);
  cam.samples_per_pixel = 10;
  cam.camera_pos = point3f(13.0f, 2.0f, 3.0f);
  cam.look_at = point3f(0.0f, 0.0f, 0.0f);

  cam.render(world);

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Render time: " << elapsed.count() << " seconds\n";
}