#ifndef HEADER_COLOR_RECTANGLE
#define HEADER_COLOR_RECTANGLE

#include "../../tools/ini_configuration.hh"

#include "image.h"

class ColorRectangle : public Image
{
public:
    ColorRectangle(unsigned width, unsigned height)
        : Image(width, height) {}

    img::EasyImage generate();
};

img::EasyImage generate_color_rectangle_image(const ini::Configuration &config);

#endif