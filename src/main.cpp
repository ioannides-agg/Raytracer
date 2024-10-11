#include <iostream>

int main() {
    int width = 256;
    int height = 256;

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";
    
    for (int i = 0; i < height; i++) {
        std::clog << "\rScanlines remaining: " << (height - i) << " " << std::flush;
        for (int j = 0; j < width; j++) {
            double r = double(j) / (width-1);
            double g = double(i) / (height-1);
            double b = 0.0;

            int R = int(256 * r);
            int G = int(256 * g);
            int B = int(256 * b);

            std::cout << R << ' ' << G << ' ' << B << "\n";
        }
    }
    

    return 0;
}