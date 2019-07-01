#include "image.h"
#include <cmath>

img::EasyImage Image::draw_2d_lines(Lines2D& lines, int size)
{
    // TODO: INT_MAX
    int x_min = 9999, x_max = 0, y_min = 9999, y_max = 0;

    for (Line2D line : lines) {
        if (line.p1.x < x_min) x_min = line.p1.x;
        if (line.p1.y < y_min) y_min = line.p1.y;
        if (line.p1.x > x_max) x_max = line.p1.x;
        if (line.p1.y > y_max) y_max = line.p1.y;
        if (line.p2.x < x_min) x_min = line.p2.x;
        if (line.p2.y < y_min) y_min = line.p2.y;
        if (line.p2.x > x_max) x_max = line.p2.x;
        if (line.p2.y > y_max) y_max = line.p2.y;
    }

    int x_range = x_max - x_min;
    int y_range = y_max - y_min;

    int image_x = size * x_range / std::max(x_range, y_range);
    int image_y = size * y_range / std::max(x_range, y_range);

    double d = 0.95 * size / std::max(x_range, y_range);

    double d_center_x = d * (x_min + x_max) / 2;
    double d_center_y = d * (y_min + y_max) / 2;

    double d_x = image_x / 2 - d_center_x;
    double d_y = image_y / 2 - d_center_y;

    for (Line2D line: lines) {
        this->img.draw_line(
            round_to_int(d * line.p1.x + d_x),
            round_to_int(d * line.p1.y + d_y),
            round_to_int(d * line.p2.x + d_x),
            round_to_int(d * line.p2.y + d_y),
            line.c
        );
    }

    return this->img;
}
