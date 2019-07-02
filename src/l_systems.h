#ifndef HEADER_L_SYSTEMS
#define HEADER_L_SYSTEMS

#include <list>
#include <map>
#include <set>

#include "image.h"
#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"
#include "tools/lparser.h"

class LSystem2D
{
public:
    // std::set<char> alphabet;
    // std::map<char, int> draw_function;
    // std::map<char, std::string> rules;
    // const char initiator;
    // const double angle_deg;
    // const double initial_angle_deg;
    // const int iterations;
    LParser::LSystem2D lsystem;
    const int size;
    const img::Color color_background;
    const img::Color color;

    LSystem2D(LParser::LSystem2D lsystem, int size, img::Color c_background, img::Color c)
        : lsystem(lsystem), size(size), color_background(c_background), color(c) {}

    img::EasyImage generate();
};

img::EasyImage generate_l_system_2d(const ini::Configuration &config);

#endif