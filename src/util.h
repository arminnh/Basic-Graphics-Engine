#ifndef HEADER_UTIL
#define HEADER_UTIL

#include <cmath>
#include <iostream>
#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"

inline int round_to_int(double d)
{
	return d < 0 ? std::ceil(d - 0.5) : std::floor(d + 0.5);
}

inline double deg_to_rad(double degrees)
{
	return degrees * M_PI / 180.0;
}

inline double rad_to_deg(double radians)
{
	return radians * 180.0 / M_PI;
}

inline img::Color tuple_to_color(ini::DoubleTuple tuple)
{
	return img::Color(
		round_to_int(255.0 * tuple[0]),
		round_to_int(255.0 * tuple[1]),
		round_to_int(255.0 * tuple[2])
	);
}

#endif