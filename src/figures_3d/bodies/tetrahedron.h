#ifndef HEADER_TETRAHEDRON
#define HEADER_TETRAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Tetrahedron : public Figure
{
public:
    Tetrahedron(ini::Section &config);
};

#endif