#ifndef HEADER_DODECAHEDRON
#define HEADER_DODECAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Dodecahedron : public Figure
{
public:
    Dodecahedron(ini::Section &config)
        : Figure(config)
    {

    }
};

#endif