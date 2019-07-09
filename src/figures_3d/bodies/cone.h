#ifndef HEADER_CONE
#define HEADER_CONE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Cone : public Figure
{
public:
    Cone(ini::Section &config);
};

#endif