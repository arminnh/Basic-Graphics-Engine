#ifndef HEADER_LINE_STRUCTURE
#define HEADER_LINE_STRUCTURE

#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"
#include "image.h"

class LineStructure : public Image
{
protected:
    const std::string structure_type;
    img::Color color_background;
    img::Color color_lines;
    const int nr_lines;

public:
    LineStructure(unsigned width, unsigned height, std::string type, ini::DoubleTuple c_background, ini::DoubleTuple c_line, int nr_lines)
        : Image(width, height), structure_type(type), nr_lines(nr_lines)
    {
        this->color_background = tuple_to_color(c_background);
        this->color_lines = tuple_to_color(c_line);

        this->img.clear(this->color_background);
    }

    void draw_quarter_circle(const int x_from, const int y_from, const int x_to, const int y_to, const int x_corner, const int y_corner);

    img::EasyImage generate();
};

img::EasyImage generate_line_structure(const ini::Configuration &config);

#endif