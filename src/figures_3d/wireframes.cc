#include <exception>

#include "../matrices.h"
#include "bodies/cone.h"
#include "bodies/cube.h"
#include "bodies/cylinder.h"
#include "bodies/dodecahedron.h"
#include "bodies/icosahedron.h"
#include "bodies/l_system_3d.h"
#include "bodies/octahedron.h"
#include "bodies/sphere.h"
#include "bodies/tetrahedron.h"
#include "bodies/torus.h"
#include "line_drawings.h"
#include "wireframes.h"

Figure* create_figure_from_config(ini::Section fig_config, Vector3D eye_point) {
    Figure* figure = nullptr;

    const std::string figure_type = fig_config["type"].as_string_or_die();
    Vector3D center = tuple_to_vector(fig_config["center"].as_double_tuple_or_die());
    const double rotate_x_degrees = fig_config["rotateX"].as_double_or_die();
    const double rotate_y_degrees = fig_config["rotateY"].as_double_or_die();
    const double rotate_z_degrees = fig_config["rotateZ"].as_double_or_die();
    const double scale = fig_config["scale"].as_double_or_die();

    if (figure_type == "LineDrawing") {
        figure = new LineDrawing(fig_config);
    } else if (figure_type == "Cube") {
        figure = new Cube(fig_config);
    } else if (figure_type == "Tetrahedron") {
        figure = new Tetrahedron(fig_config);
    } else if (figure_type == "Octahedron") {
        figure = new Octahedron(fig_config);
    } else if (figure_type == "Icosahedron") {
        figure = new Icosahedron(fig_config);
    } else if (figure_type == "Dodecahedron") {
        figure = new Dodecahedron(fig_config);
    } else if (figure_type == "Cylinder") {
        figure = new Cylinder(fig_config);
    } else if (figure_type == "Cone") {
        figure = new Cone(fig_config);
    } else if (figure_type == "Sphere") {
        figure = new Sphere(fig_config);
    } else if (figure_type == "Torus") {
        figure = new Torus(fig_config);
    } else if (figure_type == "3DLSystem") {
        figure = new LSystem3D(fig_config);
    } else {
        std::cerr << "Unreconized figure type '" + figure_type + "'" << std::endl;
        // throw exception("Unreconized figure type '" + figure_type + "'");
    }

    if (figure != nullptr) {
        if (VERBOSE) {
            std::cout << figure->to_string() << std::endl;
        }

        Matrix all_transformations = get_all_transformations_matrix(
            eye_point, center, rotate_x_degrees, rotate_y_degrees, rotate_z_degrees, scale);
        figure->apply_transformation(all_transformations);
    }

    return figure;
}

img::EasyImage generate_wireframe_image(const ini::Configuration& config) {
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