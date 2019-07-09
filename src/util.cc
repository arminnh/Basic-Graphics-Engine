#include "util.h"

std::ostream &operator<<(std::ostream &out, const Point2D &p)
{
	out << "(" << p.x << ", " << p.y << ")";
	return out;
}

std::ostream &operator<<(std::ostream &out, const Line2D &l)
{
	out << l.p1 << ", " << l.p2;
	return out;
}

img::EasyImage draw_2d_lines(Lines2D& lines, int size, img::Color c_background)
{
    // TODO: INT_MAX
    double x_min = 9999, x_max = -1, y_min = 9999, y_max = -1;

    for (Line2D line : lines) {
        if (line.p1.x < x_min) x_min = line.p1.x;
        if (line.p2.x < x_min) x_min = line.p2.x;
        if (line.p1.x > x_max) x_max = line.p1.x;
        if (line.p2.x > x_max) x_max = line.p2.x;

        if (line.p1.y < y_min) y_min = line.p1.y;
        if (line.p2.y < y_min) y_min = line.p2.y;
        if (line.p1.y > y_max) y_max = line.p1.y;
        if (line.p2.y > y_max) y_max = line.p2.y;
    }

    double x_range = x_max - x_min;
    double y_range = y_max - y_min;

    int image_x = std::max(30, round_to_int(size * x_range / std::max(x_range, y_range)));
    int image_y = std::max(30, round_to_int(size * y_range / std::max(x_range, y_range)));

    double d = 0.95 * size / std::max(x_range, y_range);

    double d_center_x = d * (x_min + x_max) / 2;
    double d_center_y = d * (y_min + y_max) / 2;

    double d_x = image_x / 2 - d_center_x;
    double d_y = image_y / 2 - d_center_y;

    if (VERBOSE) {
        std::cout << "x_min: " << x_min << ", x_max: " << x_max << ", y_min: "
            << y_min << ", y_max: " << y_max << std::endl << "x_range: " << x_range
            << ", y_range: " << y_range << ", image_x: " << image_x << ", image_y: "
            << image_y << std::endl << "d: " << d << ", d_center_x: " << d_center_x << ", d_center_y: " << d_center_y
            << ", d_x: " << d_x << ", d_y: " << d_y << std::endl;
    }

	img::EasyImage img = img::EasyImage(image_x, image_y, c_background);
    for (Line2D line: lines) {
        Line2D new_line = Line2D(
            round_to_int(d * line.p1.x + d_x),
            round_to_int(d * line.p1.y + d_y),
            round_to_int(d * line.p2.x + d_x),
            round_to_int(d * line.p2.y + d_y)
        );

        if (VERBOSE) {
            std::cout << line << "->" << new_line << std::endl;
        }

        try {
            img.draw_line(
                round_to_int(d * line.p1.x + d_x),
                round_to_int(d * line.p1.y + d_y),
                round_to_int(d * line.p2.x + d_x),
                round_to_int(d * line.p2.y + d_y),
                line.c
            );
        } catch (...) {
            std::cout << "Cannot draw line " << new_line << std::endl;
        }
    }

    return img;
}