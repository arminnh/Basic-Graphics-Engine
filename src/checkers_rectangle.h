#ifndef HEADER_CHECKERS_RECTANGLE
#define HEADER_CHECKERS_RECTANGLE

#include "image.h"
#include "tools/ini_configuration.hh"

class CheckersRectangle : public Image
{
private:
    const unsigned nr_x_blocks;
    const unsigned nr_y_blocks;
    img::Color color_white;
    img::Color color_black;

public:
    CheckersRectangle(unsigned width, unsigned height, unsigned n_x, unsigned n_y, ini::DoubleTuple c_white, ini::DoubleTuple c_black, bool c_invert)
        : Image(width, height), nr_x_blocks(n_x), nr_y_blocks(n_y)
    {
        this->color_white = tuple_to_color(c_white);
        this->color_black = tuple_to_color(c_black);

        if (c_invert) {
            std::swap(this->color_white, this->color_black);
        }
    }

    img::EasyImage generate();
};

img::EasyImage generate_checkers_rectangle(const ini::Configuration &config);

#endif