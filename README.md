# Raytracer

This project is animplementation of a raytracer. It has been heavily altered over the months as I have grown as a programmer, applying new concepts and adopting different approaches to tackle the same problem. The raytracer is based on the famous *Ray Tracing in One Weekend* e-book:

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

## Improving on the Book

After building the raytracer, I noticed that the slow performance for complex scenes with even minimal anti-aliasing was a nuisance. To address this, I started implementing different approaches to speed up execution.

### 1. Multi-Threading

Running the rendering process on multiple threads is a no-brainer, as the rendering process for each row is fairly independent of the others. Testing on the complex scene from the book with 10 samples per pixel, using 8 threads versus the classical single-threaded approach, yielded the following results (measured using `std::chrono` for non-blocking timing):

   ```sh
   Multithreading: 440.958 seconds (~7.33 minutes)
   Classic: 1610.18 seconds (~26.83 minutes)
   ```

This speed-up is massive, reducing the rendering time by almost 4x. However, 7 minutes is still a significant amount of time for rendering, so further optimizations are planned.