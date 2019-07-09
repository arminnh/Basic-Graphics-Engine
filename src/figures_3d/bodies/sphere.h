#ifndef HEADER_SPHERE
#define HEADER_SPHERE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Sphere : public Figure
{
public:
    Sphere(ini::Section &config);
};

#endif