#ifndef HEADER_CYLINDER
#define HEADER_CYLINDER

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Cylinder : public Figure
{
public:
    Cylinder(ini::Section &config)
        : Figure(config)
    {
        const int n = config["n"].as_int_or_die();
        const double height = config["height"].as_double_or_die();
    }
};

#endif