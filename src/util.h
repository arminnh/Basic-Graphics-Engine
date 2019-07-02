#ifndef HEADER_UTIL
#define HEADER_UTIL

#include <list>
#include <cmath>
#include <iostream>
#include "tools/EasyImage.h"
#include "tools/ini_configuration.hh"

class Point2D
{
public:
	double x;
	double y;

	Point2D(double x, double y) : x(x), y(y) {};
};

class Line2D
{
public:
	Point2D p1;
	Point2D p2;
	img::Color c = img::Color(255, 255, 255);

	Line2D(Point2D p1, Point2D p2) : p1(p1), p2(p2) {};

	Line2D(Point2D p1, Point2D p2, img::Color c) : p1(p1), p2(p2), c(c) {};

	Line2D(double x1, double y1, double x2, double y2) : p1(Point2D(x1, y1)), p2(Point2D(x2, y2)) {};

	Line2D(double x1, double y1, double x2, double y2, img::Color c) : p1(Point2D(x1, y1)), p2(Point2D(x2, y2)), c(c) {};
};

typedef std::list<Line2D> Lines2D;

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

img::EasyImage draw_2d_lines(Lines2D& lines, int size);

#endif