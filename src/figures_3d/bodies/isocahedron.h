#ifndef HEADER_ISOCAHEDRON
#define HEADER_ISOCAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Isocahedron : public Figure
{
public:
    Isocahedron(ini::Section &config)
        : Figure(config)
    {

    }
};

#endif