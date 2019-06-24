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
    const bool invert_colors;

public:
    CheckersRectangle(
        unsigned width, unsigned height, unsigned n_x, unsigned n_y,
        ini::DoubleTuple c_white, ini::DoubleTuple c_black, bool c_invert
    ) : Image(width, height), nr_x_blocks(n_x), nr_y_blocks(n_y), invert_colors(c_invert)
    {
        this->color_white = img::Color(
            round_to_int(255.0 * c_white[0]),
            round_to_int(255.0 * c_white[1]),
            round_to_int(255.0 * c_white[2])
        );

        this->color_black = img::Color(
            round_to_int(255.0 * c_black[0]),
            round_to_int(255.0 * c_black[1]),
            round_to_int(255.0 * c_black[2])
        );

        if (invert_colors) {
            std::swap(this->color_white, this->color_black);
        }
    }

    img::EasyImage generate();
};

img::EasyImage generate_checkers_rectangle(const ini::Configuration &config);

#endif