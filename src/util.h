#ifndef HEADER_UTIL
#define HEADER_UTIL

#include <cmath>
#include <iostream>

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

#endif