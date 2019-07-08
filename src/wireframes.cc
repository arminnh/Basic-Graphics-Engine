#include "matrices.h"
#include "wireframes.h"
#include "line_drawings.h"
#include <exception>

img::EasyImage generate_wireframe_drawing(const ini::Configuration &config)
{
    const int size = config["General"]["size"].as_int_or_die();
    const ini::DoubleTuple c_background = config["General"]["backgroundcolor"].as_double_tuple_or_die();
    const int nr_figures = config["General"]["nrFigures"].as_int_or_die();
    const Vector3D eye_point = tuple_to_vector(config["General"]["eye"].as_double_tuple_or_die());

    Lines2D lines;
    Figure *figure;

    for (int fig_nr = 0; fig_nr < nr_figures; fig_nr++) {
        ini::Section fig_config = config["Figure" + std::to_string(fig_nr)];
        const std::string figure_type = fig_config["type"].as_string_or_die();
        const double rotate_x_degrees = fig_config["rotateX"].as_double_or_die();
        const double rotate_y_degrees = fig_config["rotateY"].as_double_or_die();
        const double rotate_z_degrees = fig_config["rotateZ"].as_double_or_die();
        const double scale = fig_config["scale"].as_double_or_die();

        figure = nullptr;

        std::cout << "Loading figure " << fig_nr << std::endl;
        if (figure_type == "LineDrawing") {
            figure = new LineDrawing(fig_config);
        } else {
            std::cerr << "Unreconized figure type '" + figure_type + "'" << std::endl;
            // throw exception("Unreconized figure type '" + figure_type + "'");
        }

        if (figure != nullptr) {
            std::cout << figure->to_string() << std::endl;

            // transformation operations on figure
            figure->apply_transformation(get_eye_point_transformation_matrix(eye_point));

            // collect 2D lines
            int i = 0;
            for (Line2D line : figure->project(eye_point, 1)) {
                lines.push_back(line);
                std::cout << "Line " << i << ": " << line << std::endl;
                i++;
            }
            std::cout << "Added lines" << std::endl;
        }

    }

    delete figure;

    std::cout << "Generated wireframe drawing" << std::endl;

    return draw_2d_lines(lines, size, tuple_to_color(c_background));
}