#pragma once

#include "vec3.h"
#include <iostream>

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    int R = int(255.999 * r);
    int G = int(255.999 * g);
    int B = int(255.999 * b);

    out << R << " " << G << " " << B << "\n";
}
