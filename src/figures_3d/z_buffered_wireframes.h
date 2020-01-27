#ifndef HEADER_Z_BUFFERING
#define HEADER_Z_BUFFERING

#include <limits>
#include "../tools/EasyImage.h"
#include "../tools/ini_configuration.hh"

/**
 * Class to hold smallest 1/z value for each pixel of an image. Initializes all values to +inf.
 */
class ZBuffer : public std::vector<std::vector<double>> {
   public:
    // Initializes a Z-Buffer of width*height and initializes values to +inf.
    ZBuffer(int width, int height) {
        this->resize(height, std::vector<double>(width, std::numeric_limits<double>::infinity()));
        // std::cout << "Z buffer size: " << this->size() << std::endl;

        // std::cout << "0, 0: " << this->at(0).at(0) << std::endl;
        // this->at(0).at(0) = 5;
        // std::cout << "0, 0: " << this->at(0).at(0) << std::endl;

        // std::cout << "1, 1: " << this->at(1).at(1) << std::endl;

        // std::cout << height -1 << ", " << width -1 << ": " << this->at(height - 1).at(width -1) << std::endl;
        // this->at(height - 1).at(width -1) = 0.12345;
        // std::cout << height -1 << ", " << width -1 << ": " << this->at(height - 1).at(width -1) << std::endl;
    }
};

img::EasyImage generate_z_buffered_wireframe_image(const ini::Configuration &config);

void draw_zbuf_line(ZBuffer &z_buffer, img::EasyImage &img,
                    unsigned int x1, unsigned int y1, double z1,
                    unsigned int x2, unsigned int y2, double z2, img::Color color);

#endif