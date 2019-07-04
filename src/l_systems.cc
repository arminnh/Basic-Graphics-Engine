#include <fstream>
#include "l_systems.h"
#include "tools/ini_configuration.hh"
#include "util.h"
#include "image.h"

std::string LSystem2D::apply_rules(std::string sequence, int iterations)
{
    std::cout << "apply on '" << sequence << "' , " << iterations << std::endl;
    if (iterations == 0) {
        return sequence;
    }

    iterations--;
    std::string new_sequence;

    for (char c: sequence) {
        if (this->lsystem.get_alphabet().count(c)) {
            new_sequence += this->apply_rules(this->lsystem.get_replacement(c), iterations);
        } else {
            new_sequence += c;
        }
    }

    return new_sequence;
}

img::EasyImage LSystem2D::generate()
{
    Lines2D lines;

    std::set<char> alphabet = this->lsystem.get_alphabet();
    double current_angle = deg_to_rad(this->lsystem.get_starting_angle());
    Point2D current_p = Point2D(0, 0);
    std::string sequence = this->apply_rules(this->lsystem.get_initiator(), this->lsystem.get_nr_iterations());
    std::cout << "sequence: " << sequence << std::endl;

    for (char c : sequence) {
        if (alphabet.count(c)) {
            if (this->lsystem.draw(c)) {
                double d_x = std::cos(current_angle);
                double d_y = std::sin(current_angle);
                Point2D next_p = Point2D(current_p.x + d_x, current_p.y + d_y);
                lines.push_back(Line2D(current_p, next_p, this->color));
                current_p = next_p;
            }
        } else if (c == '+') {
            current_angle += deg_to_rad(this->lsystem.get_angle());
        } else if (c == '-') {
            current_angle -= deg_to_rad(this->lsystem.get_angle());
        }
    }

    // std::cout << lines << std::endl;
    // for (Line2D line : lines) {
    //     std::cout << line << std::endl;
    // }

    return draw_2d_lines(lines, this->size, this->color_background);
}

img::EasyImage generate_l_system_2d(const ini::Configuration &config)
{
    const int size = config["General"]["size"].as_int_or_die();
    const ini::DoubleTuple c_background = config["General"]["backgroundcolor"].as_double_tuple_or_die();

    const std::string inputfile = config["2DLSystem"]["inputfile"].as_string_or_die();
    const ini::DoubleTuple c = config["2DLSystem"]["color"].as_double_tuple_or_die();

    LParser::LSystem2D l_system;
    std::ifstream input_stream("images/2D_l_systems/" + inputfile);
    input_stream >> l_system;
    input_stream.close();

    return LSystem2D(l_system, size, tuple_to_color(c_background), tuple_to_color(c))
        .generate();
}