cmake_minimum_required(VERSION 3.30)
project(raytracer VERSION 0.1.0)

add_executable(raytracer
    src/main.cpp
)

set_property(TARGET raytracer PROPERTY CXX_STANDARD 20)