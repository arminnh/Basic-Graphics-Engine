#ifndef HEADER_ISOCAHEDRON
#define HEADER_ISOCAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Icosahedron : public Figure
{
public:
    Icosahedron(ini::Section &config)
        : Figure(config)
    {

    }
};

#endif