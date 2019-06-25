#ifndef HEADER_LINE_STRUCTURE
#define HEADER_LINE_STRUCTURE

#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"
#include "image.h"

class LineStructure : public Image
{
protected:
    img::Color color_background;
    img::Color color_lines;
    const int nr_lines;

public:
    LineStructure(unsigned width, unsigned height, ini::DoubleTuple c_background, ini::DoubleTuple c_line, int nr_lines) 
        : Image(width, height), nr_lines(nr_lines)
    {
        this->color_background = tuple_to_color(c_background);
        this->color_lines = tuple_to_color(c_line);

        this->img.clear(this->color_background);
    }

    virtual img::EasyImage generate() = 0;
};

class QuarterCircle : public LineStructure
{
public:
    QuarterCircle(unsigned width, unsigned height, ini::DoubleTuple c_background, ini::DoubleTuple c_line, int nr_lines) 
        : LineStructure(width, height, c_background, c_line, nr_lines) {}

    img::EasyImage generate();
};

img::EasyImage generate_line_structure(const ini::Configuration &config);

#endif