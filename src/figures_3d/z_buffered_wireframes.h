#ifndef HEADER_Z_BUFFERING
#define HEADER_Z_BUFFERING

#include "../tools/EasyImage.h"
#include "../tools/ini_configuration.hh"

img::EasyImage generate_z_buffered_wireframe_image(const ini::Configuration &config);

#endif