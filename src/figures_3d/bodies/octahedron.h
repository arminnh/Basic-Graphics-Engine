#ifndef HEADER_OCTAHEDRON
#define HEADER_OCTAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Octahedron : public Figure
{
public:
    Octahedron(ini::Section &config)
        : Figure(config)
    {

    }
};

#endif