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
    Cylinder(ini::Section &config);
};

#endif