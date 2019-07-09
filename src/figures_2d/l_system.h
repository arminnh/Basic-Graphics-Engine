#ifndef HEADER_L_SYSTEMS
#define HEADER_L_SYSTEMS

#include <list>
#include <map>
#include <set>

#include "../tools/EasyImage.h"
#include "../tools/ini_configuration.hh"
#include "../tools/lparser.h"

class LSystem2D
{
public:
    LParser::LSystem2D lsystem;
    const int size;
    const img::Color color_background;
    const img::Color color;

    LSystem2D(LParser::LSystem2D lsystem, int size, img::Color c_background, img::Color c)
        : lsystem(lsystem), size(size), color_background(c_background), color(c) {}

    img::EasyImage generate();

private:
    std::string apply_rules(std::string sequence, int iterations);
};

img::EasyImage generate_l_system_2d_image(const ini::Configuration &config);

#endif