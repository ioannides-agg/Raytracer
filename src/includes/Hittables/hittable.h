#pragma once
#include "ray.h"
#include "vec3.h"

class hit_record {
    public:
    point3 p;
    vec3 normal;
    double t;
};