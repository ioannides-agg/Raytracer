#include "config.h"

using color = vec3f;
color white = color(1.0f, 1.0f, 1.0f);
color blue = color(0.5f, 0.7f, 1.0f);
color red = color(1.0f, 0.0f, 0.0f);

color color_ray(Ray& r, const hittable_object& world) {
    hit_record hit;
    if(world.hit(r, hit, interval(0, infinity))) {
        vec3f color = (hit.normal + white);
        return 0.5f * color;
    }

    //background sky gradient
    vec3f dir = r.direction();
    float a = 0.5f * (dir.normalized()[1] + 1.0f);
    return (1.0f - a) * white + a * blue;
}

int main() {
    //viewport
    const point3f camera_pos;
    const float fov = rad(90);
    const int width = 1024;
    const int height = 768;
    const auto aspect_ratio = width/float(height);
    std::vector<color> framebuffer;

    //objects to render
    hittable_list world;
    world.add(std::make_shared<Sphere>(point3f(0.0f,0.0f,-1.0f), 0.5f));
    world.add(std::make_shared<Sphere>(point3f(0.0f,-100.5f,-1.0f), 100.0f));

    for (size_t i = 0; i < height; i++) {
        std::clog << "\rLines Remaining: " << height - i << " " << std::flush;
        for (size_t j = 0; j < width; j++) {
            //Calculating the screen size
            float x = (2*(j+0.5)/float(width) - 1) * tan(fov/2.) * aspect_ratio;
            float y = -(2*(i+0.5)/float(height) - 1) * tan(fov/2.);
            vec3f direction = vec3f(x,y,-1.0f);
            Ray ray = Ray(camera_pos, direction);
            color Color = color_ray(ray, world);

            framebuffer.push_back(Color);
        }    
    }

    PPM_image_writer("../images/render.ppm", width, height, framebuffer);

    return 0;
}