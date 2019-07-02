#include <fstream>
#include "l_systems.h"
#include "tools/ini_configuration.hh"
#include "util.h"
#include "image.h"

img::EasyImage LSystem2D::generate()
{
    Lines2D lines;

    std::set<char> const alphabet = this->lsystem.get_alphabet();



    return draw_2d_lines(lines, this->size);
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