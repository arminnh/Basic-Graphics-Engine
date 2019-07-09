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
    Torus(ini::Section &config);
};

#endif