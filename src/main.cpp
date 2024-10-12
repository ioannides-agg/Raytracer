#include "config.h"

int main() {
    int width = 256;
    int height = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int i = 0; i < height; i++) {
        std::clog << "\rScanlines remaining: " << (height - i) << " " << std::flush;
        for (int j = 0; j < width; j++) {
            color pixel_color = color(double(j)/(width-1), double(i)/(height-1), 0);
            write_color(std::cout, pixel_color);
        }
    }
    
    return 0;
}