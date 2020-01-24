#include "z_buffered_wireframes.h"
#include "figure.h"
#include "../matrices.h"
#include "../util.h"
#include "wireframes.h"

img::EasyImage generate_z_buffered_wireframe_image(const ini::Configuration& config) {
    const int size = config["General"]["size"].as_int_or_die();
    const ini::DoubleTuple c_background = config["General"]["backgroundcolor"].as_double_tuple_or_die();
    const int nr_figures = config["General"]["nrFigures"].as_int_or_die();
    const Vector3D eye_point = tuple_to_vector(config["General"]["eye"].as_double_tuple_or_die());

    Lines2D lines;
    Figure* figure;

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
            delete figure;
        }
    }

    std::cout << "Generated wireframe drawing" << std::endl;

    return draw_2d_lines(lines, size, tuple_to_color(c_background));
}