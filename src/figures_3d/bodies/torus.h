#ifndef HEADER_TORUS
#define HEADER_TORUS

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Torus : public Figure
{
public:
    Torus(ini::Section &config)
        : Figure(config)
    {
        const double r_middle = config["R"].as_double_or_die();
        const double r_torus = config["r"].as_double_or_die();
        const int n = config["n"].as_int_or_die();
        const int m = config["m"].as_int_or_die();
    }
};

#endif