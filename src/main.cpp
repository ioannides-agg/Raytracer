#include "config.h"

double hit_sphere(const point3& center, double radius, const ray& r) {

    //we calculate how many solutions t exist for the equation:
    //(C-P)*(C-P) = r^2 where P(t) the function describing a ray with Q+td 
    //where Q origin of ray and d the direction.
    //so we solve for (C-P(t))*(C-P(t)) = r^2 <=>
    //... <=> t^2 *d*d - 2t*d*(C-Q) + (C-Q)*(C-Q) - r^2 = 0

    /*vec3 oc = center - r.origin();
    double a = dot(r.direction(), r.direction());
    double b = -2.0 * dot(r.direction(), oc);
    double c = dot(oc, oc) - radius*radius;*/

    //next we shall simplify the expression, with b = -2h (where h = dot(r.direction(), oc))

    vec3 oc = center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() -  radius*radius;

    double discriminant = h*h - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / a;
    }
    
    //return discriminant < 0? -1.0 : (-b - std::sqrt(discriminant)) / (2.0*a);
}

color ray_color(const ray& r) {
    //if ray passes through the sphere with r = 0.5 draw the sphere
    double d = hit_sphere(point3(0,0,-1), 0.5, r);

    if (d > 0) {
        vec3 normal = unit_vector(r.at(d) - vec3(0,0,-1));
        return 0.5*color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unit_ray_direction = unit_vector(r.direction());
    double alpha = 0.5*(unit_ray_direction.y() + 1.0);
    return (1.0 - alpha) * color(1.0, 1.0, 1.0) + alpha * color(0.2, 0.4, 1.0);
}

int main() {
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    //calculate image_height
    int image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    //Basic Camera
    double focal_length = 1.0;
    //calculate viewport
    double height = 2.0;
    double width = height * (double(image_width)/image_height);
    point3 camera_center = point3(0, 0, 0);

    //calculate horiztonal and top down vectors, u and v respectively
    vec3 u = vec3(width, 0, 0);
    vec3 v = vec3(0, -height, 0);

    //calculate the delta of the vectors u, v
    vec3 delta_u = u / image_width;
    vec3 delta_v = v / image_height;

    //calculate position of the upper left pixel Q
    vec3 Q = camera_center - vec3(0, 0, focal_length) - u/2 - v/2;
    point3 Qloc = Q + 0.5 * (delta_u + delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; i++) {
            point3 pixel_center = Qloc + (i * delta_u) + (j * delta_v);
            vec3 ray_dir = pixel_center - camera_center;
            ray r(camera_center, ray_dir);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    
    return 0;
}