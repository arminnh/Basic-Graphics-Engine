#ifndef HEADER_CUBE
#define HEADER_CUBE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Cube : public Figure
{
public:
    Cube(ini::Section &config)
        : Figure(config)
    {

    }
};

#endif