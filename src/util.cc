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

img::EasyImage draw_2d_lines(const Lines2D& lines, const int size, const img::Color c_background)
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

    const double x_range = x_max - x_min;
    const double y_range = y_max - y_min;

    const int image_x = std::max(30, round_to_int(size * x_range / std::max(x_range, y_range)));
    const int image_y = std::max(30, round_to_int(size * y_range / std::max(x_range, y_range)));

    const double d = 0.95 * size / std::max(x_range, y_range);

    const double d_center_x = d * (x_min + x_max) / 2;
    const double d_center_y = d * (y_min + y_max) / 2;

    const double d_x = image_x / 2 - d_center_x;
    const double d_y = image_y / 2 - d_center_y;

    std::cout << "x_min: " << x_min << ", x_max: " << x_max << ", y_min: "
        << y_min << ", y_max: " << y_max << std::endl << "x_range: " << x_range
        << ", y_range: " << y_range << ", image_x: " << image_x << ", image_y: "
        << image_y << std::endl << "d: " << d << ", d_center_x: " << d_center_x << ", d_center_y: " << d_center_y
        << ", d_x: " << d_x << ", d_y: " << d_y << std::endl;

	img::EasyImage img = img::EasyImage(image_x, image_y, c_background);
    for (Line2D old_line: lines) {
        Line2D line = Line2D(
            round_to_int(d * old_line.p1.x + d_x),
            round_to_int(d * old_line.p1.y + d_y),
            round_to_int(d * old_line.p2.x + d_x),
            round_to_int(d * old_line.p2.y + d_y),
            old_line.c
        );

        if (VERBOSE) {
            std::cout << old_line << "->" << line << std::endl;
        }

        if (0 <= line.p1.x && line.p1.x < image_x && 0 <= line.p1.y && line.p1.y < image_y
            &&  0 <= line.p2.x && line.p2.x < image_x &&  0 <= line.p2.y && line.p2.y < image_y) {

            img.draw_line(line.p1.x, line.p1.y, line.p2.x, line.p2.y, line.c);
        } else {
            std::cerr << "Cannot draw line " << line << std::endl;
        }
    }

    return img;
}