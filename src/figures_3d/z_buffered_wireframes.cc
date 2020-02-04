#include "z_buffered_wireframes.h"
#include <assert.h>
#include "../util/transformation_matrices.h"
#include "../util/util.h"
#include "figure.h"
#include "wireframes.h"

img::EasyImage generate_z_buffered_wireframe_image(const ini::Configuration &config) {
    const int size = config["General"]["size"].as_int_or_die();
    const ini::DoubleTuple c_background = config["General"]["backgroundcolor"].as_double_tuple_or_die();
    const int nr_figures = config["General"]["nrFigures"].as_int_or_die();
    const Vector3D eye_point = tuple_to_vector(config["General"]["eye"].as_double_tuple_or_die());

    Lines2D lines;
    Figure *figure;

    for (int fig_nr = 0; fig_nr < nr_figures; fig_nr++) {
        std::cout << "Loading figure " << fig_nr << std::endl;
        ini::Section fig_config = config["Figure" + std::to_string(fig_nr)];

        figure = create_figure_from_config(fig_config, eye_point);

        if (figure != nullptr) {
            // collect 2D lines
            int i = 0;
            for (Line2D line : figure->project(1)) {
                lines.push_back(line);
                if (VERBOSE) {
                    std::cout << "Line " << i << ": " << line << std::endl;
                }
                i++;
            }
            std::cout << "Added lines for figure " << fig_nr << std::endl;
            // delete figure;
        }
    }

    std::cout << "Generated z buffered wireframe drawing" << std::endl;

    return draw_2d_lines_z_buffered(lines, size, tuple_to_color(c_background));
}

void draw_zbuf_line(ZBuffer &z_buffer, img::EasyImage &img,
                    unsigned int x1, unsigned int y1, double z1,
                    unsigned int x2, unsigned int y2, double z2, img::Color color) {
    assert(x1 < img.get_width() && y1 < img.get_height());
    assert(x2 < img.get_width() && y2 < img.get_height());

    // std::cout << "x1: " << x1 << ", "
    //           << "y1: " << y1 << ", "
    //           << "z1: " << z1 << ", "
    //           << "x2: " << x2 << ", "
    //           << "y2: " << y2 << ", "
    //           << "z2: " << z2 << ", " << std::endl;

    if (x1 == x2 && y1 == y2) {
        if (1 / z1 < z_buffer(x1, y1)) {
            z_buffer(x1, y1) = 1 / z1;
            img(x1, y1) = color;
        }

    } else if (x1 == x2) {
        // vertical line
        for (unsigned int y_i = std::min(y1, y2); y_i <= std::max(y1, y2); y_i++) {
            double loop_ratio = (y_i - std::min(y1, y2)) / (std::max(y1, y2) - std::min(y1, y2));
            double z = z1 + loop_ratio * (z2 - z1);

            if (1 / z < z_buffer(x1, y_i)) {
                z_buffer(x1, y_i) = 1 / z;
                img(x1, y_i) = color;
            }
        }
    } else if (y1 == y2) {
        // horizontal line
        for (unsigned int x_i = std::min(x1, x2); x_i <= std::max(x1, x2); x_i++) {
            double loop_ratio = (x_i - std::min(x1, x2)) / (std::max(x1, x2) - std::min(x1, x2));
            double z = z1 + loop_ratio * (z2 - z1);

            if (1 / z < z_buffer(x_i, y1)) {
                z_buffer(x_i, y1) = 1 / z;
                img(x_i, y1) = color;
            }
        }
    } else {
        // line with slope m

        if (x1 > x2) {
            // flip points do x1 to has the low value
            std::swap(x1, x2);
            std::swap(y1, y2);
            std::swap(z1, z2);
        }

        double m = ((double)y2 - (double)y1) / ((double)x2 - (double)x1);

        if (-1.0 <= m && m <= 1.0) {
            // x changes more often than y, loop over x points
            for (unsigned int i = 0; i <= (x2 - x1); i++) {
                img(x1 + i, (unsigned int)round(y1 + m * i)) = color;
            }
        } else if (m > 1.0) {
            // y changes more often than x, loop over y points and draw line upwards
            for (unsigned int i = 0; i <= (y2 - y1); i++) {
                img((unsigned int)round(x1 + (i / m)), y1 + i) = color;
            }
        } else if (m < -1.0) {
            // y changes more often than x, loop over y points and draw line downwards
            for (unsigned int i = 0; i <= (y1 - y2); i++) {
                img((unsigned int)round(x1 - (i / m)), y1 - i) = color;
            }
        }
    }
}

img::EasyImage draw_2d_lines_z_buffered(const Lines2D &lines, const int size, const img::Color c_background) {
    double x_min = std::numeric_limits<double>::infinity(), y_min = std::numeric_limits<double>::infinity();
    double x_max = -std::numeric_limits<double>::infinity(), y_max = -std::numeric_limits<double>::infinity();

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

    std::cout << "x_min: " << x_min << ", x_max: " << x_max
              << ", y_min: " << y_min << ", y_max: " << y_max << std::endl
              << "x_range: " << x_range << ", y_range: " << y_range
              << ", image_x: " << image_x << ", image_y: " << image_y << std::endl
              << "d: " << d << ", d_center_x: " << d_center_x << ", d_center_y: " << d_center_y
              << ", d_x: " << d_x << ", d_y: " << d_y << std::endl;

    img::EasyImage img = img::EasyImage(image_x, image_y, c_background);
    ZBuffer z_buffer = ZBuffer(size, size);
    for (Line2D old_line : lines) {
        Line2D line = Line2D(
            round_to_int(d * old_line.p1.x + d_x),
            round_to_int(d * old_line.p1.y + d_y),
            round_to_int(d * old_line.p2.x + d_x),
            round_to_int(d * old_line.p2.y + d_y),
            old_line.c);

        if (VERBOSE) {
            std::cout << old_line << "->" << line << std::endl;
        }

        if (0 <= line.p1.x && line.p1.x < image_x && 0 <= line.p1.y && line.p1.y < image_y && 0 <= line.p2.x && line.p2.x < image_x && 0 <= line.p2.y && line.p2.y < image_y) {
            draw_zbuf_line(z_buffer, img, line.p1.x, line.p1.y, line.z1, line.p2.x, line.p2.y, line.z2, line.c);
        } else {
            std::cerr << "Cannot draw line " << line << std::endl;
        }
    }

    return img;
}
