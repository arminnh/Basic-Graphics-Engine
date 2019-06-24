#ifndef HEADER_COLOR_RECTANGLE
#define HEADER_COLOR_RECTANGLE

#include "image.h"
#include "tools/ini_configuration.hh"

class ColorRectangle : public Image
{
public:
    ColorRectangle(unsigned width, unsigned height)
        : Image(width, height) {}

    img::EasyImage generate();
};

img::EasyImage generate_color_rectangle(const ini::Configuration &config);

#endif