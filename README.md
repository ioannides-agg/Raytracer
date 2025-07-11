# Raytracer

This project is a work-in-progress implementation of a raytracer. It has been heavily altered over the months as I have grown as a programmer, applying new concepts and adopting different approaches to tackle the same problem. The raytracer is based on the famous *Ray Tracing in One Weekend* e-book:

[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html#surfacenormalsandmultipleobjects/anintervalclass)

## Building the Project

To build the project, follow these steps:

1. Navigate to the `/Raytracer/` folder.
2. Run the following command to configure the build:
   ```sh
   cmake -S . -B build

3. Run the following command:
   ```sh
   make --directory /build/

4. After that you can run the built program:
   ```sh
   ./build/raytracer

you will find the render.ppm produced inside the project directory!
   