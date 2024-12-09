#ifndef PPM_IMAGE_WRITER_H
#define PPM_IMAGE_WRITER_H

#include <fstream>

void PPM_image_writer(std::string path, auto width, auto height, auto framebuffer) { 

        std::ofstream ofs;
        ofs.open(path);
        ofs << "P3\n" << width << " " << height << "\n255\n";
        for (size_t i = 0; i < height*width; i++) {
            framebuffer[i] *= 255;
            ofs << framebuffer[i] << "\n";
            
        }

        ofs.close();
}



#endif /*PPM_IMAGE_WRITER_H*/