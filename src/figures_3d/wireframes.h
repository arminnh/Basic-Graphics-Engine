#ifndef HEADER_WIREFRAMES
#define HEADER_WIREFRAMES

#include "line_drawings.h"

Figure* create_figure_from_config(ini::Section fig_config, Vector3D eye_point);

img::EasyImage generate_wireframe_image(const ini::Configuration& config);

#endif