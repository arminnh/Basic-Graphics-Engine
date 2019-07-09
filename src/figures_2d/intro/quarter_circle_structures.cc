#include "quarter_circle_structures.h"

void LineStructure::draw_quarter_circle(const int x_from, const int y_from, const int x_to, const int y_to, const int x_corner, const int y_corner)
{
    int d_width = std::max(std::abs(x_from - x_corner), std::abs(x_to - x_corner)) / (this->nr_lines - 1);
    int d_height = std::max(std::abs(y_from - y_corner), std::abs(y_to - y_corner)) / (this->nr_lines - 1);
    int x1 = x_from, y1 = y_from, x2 = x_corner, y2 = y_corner;

    for (int line = 0; line < this->nr_lines; line++) {
        std::cout << line << ": (" << x1 << ", " << y1 << "), (" << x2 << ", " << y2 << ")" << std::endl;
        this->img.draw_line(x1, y1, x2, y2, this->color_lines);

        if (x1 < x_corner) {
            x1 += d_width;
        } else if (x1 > x_corner) {
            x1 -= d_width;
        }

        if (y1 < y_corner) {
            y1 += d_height;
        } else if (y1 > y_corner) {
            y1 -= d_height;
        }

        if (x2 < x_to) {
            x2 += d_width;
        } else if (x2 > x_to) {
            x2 -= d_width;
        }

        if (y2 < y_to) {
            y2 += d_height;
        } else if (y2 > y_to) {
            y2 -= d_height;
        }
    }
}

img::EasyImage LineStructure::generate()
{
    if (this->structure_type == "QuarterCircle") {
        this->draw_quarter_circle(0, 0, this->w - 1, this->h - 1, 0, this->h - 1);
    } else if (this->structure_type == "Eye") {
        this->draw_quarter_circle(0, 0, this->w - 1, this->h - 1, 0, this->h - 1);
        this->draw_quarter_circle(0, 0, this->w - 1, this->h - 1, this->w - 1, 0);
    } else if (this->structure_type == "Diamond") {
        this->draw_quarter_circle(0, this->h / 2, this->w / 2, this->h - 1, this->w / 2, this->h / 2);
        this->draw_quarter_circle(this->w / 2, this->h - 1, this->w - 1, this->h / 2, this->w / 2, this->h / 2);
        this->draw_quarter_circle(this->w - 1, this->h / 2, this->w / 2, 0, this->w / 2, this->h / 2);
        this->draw_quarter_circle(this->w / 2, 0, 0, this->h / 2, this->w / 2, this->h / 2);
    } else {
        std::cerr << "Unsupported structure type '" << this->structure_type << "'" << std::endl;
    }

    return this->img;
}

img::EasyImage generate_quarter_circle_structure_image(const ini::Configuration &config)
{
    const std::string structure_type = config["LineProperties"]["figure"].as_string_or_die();
    const int width = config["ImageProperties"]["width"].as_int_or_die();
    const int height = config["ImageProperties"]["height"].as_int_or_die();
    const ini::DoubleTuple c_background = config["LineProperties"]["backgroundcolor"].as_double_tuple_or_die();
    const ini::DoubleTuple c_line = config["LineProperties"]["lineColor"].as_double_tuple_or_die();
    const int nr_lines = config["LineProperties"]["nrLines"].as_int_or_die();

    return LineStructure(width, height, structure_type, c_background, c_line, nr_lines)
        .generate();
}