#ifndef HEADER_LSYSTEM_3D
#define HEADER_LSYSTEM_3D

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class LSystem3D : public Figure
{
public:
    LSystem3D(ini::Section &config);
};

#endif