#include "line_structures.h"

img::EasyImage QuarterCircle::generate()
{
    int d_width = this->w / (this->nr_lines - 1);
    int d_height = this->h / (this->nr_lines - 1);
    int x1 = 0, x2 = 0, y1 = 0, y2 = this->h - 1;

    for (int line = 0; line < this->nr_lines; line++) {
        this->img.draw_line(x1, y1, x2, y2, this->color_lines);

        y1 += d_height;
        x2 += d_width;
    }

    return this->img;
}

img::EasyImage generate_line_structure(const ini::Configuration &config)
{
    const std::string type = config["LineProperties"]["figure"].as_string_or_die();
    const int width = config["ImageProperties"]["width"].as_int_or_die();
    const int height = config["ImageProperties"]["height"].as_int_or_die();
    const ini::DoubleTuple c_background = config["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    const ini::DoubleTuple c_line = config["LineProperties"]["lineColor"].as_double_tuple_or_die();
    const int nr_lines = config["LineProperties"]["nrLines"].as_int_or_die();

    if (type == "QuarterCircle") {
        return QuarterCircle(width, height, c_background, c_line, nr_lines)
            .generate();
    }
}