#ifndef HEADER_IMAGE
#define HEADER_IMAGE

#include "../../tools/EasyImage.h"

#include "../../util/util.h"

class Image
{
protected:
    const unsigned w;
    const unsigned h;
    img::EasyImage img;

public:
    Image(unsigned size) : Image(size, size) {}

    Image(unsigned width, unsigned height)
        : w(width), h(height)
    {
        this->img = img::EasyImage(width, height);
    }

    void color_pixel(unsigned x, unsigned y, img::Color c) {
        this->img(x, y).red = c.red;
        this->img(x, y).green = c.green;
        this->img(x, y).blue = c.blue;
    }

    void color_pixel(unsigned x, unsigned y, unsigned r, unsigned g, unsigned b) {
        this->img(x, y).red = r;
        this->img(x, y).green = g;
        this->img(x, y).blue = b;
    }

    virtual img::EasyImage generate() = 0;
};

#endif