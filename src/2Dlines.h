/*****************************
* Author: Armin Halilovic
* Date: 26 februari 2013 - 8 maart 2013 
* Title: 2D lines.h
******************************/

#include "tools/ini_configuration.hh"
#include "tools/EasyImage.h"
#include "tools/lparser.h"
#include "tools/vector.hh"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <stack>
#include <list>
#define PI 3.141592653589

#ifndef L2D_H_
#define L2D_H_

using namespace std;

class Color {
 public:
	double red;
	double green;
	double blue;
};

class Point2D {
 public:
	double x; 
	double y;
};

class Line2D {
 public:
	Point2D p1;
	Point2D p2;
	Color color;
	
	double z1;
	double z2;
}; 

typedef std::list<Line2D> Lines2D;

inline int round_to_int(double d) {
	return d < 0 ? 
		std::ceil(d-0.5):
		std::floor(d+0.5);
}

img::EasyImage draw_2D_lines(Lines2D& lines, int size, img::Color color);
Lines2D convert_2DL_to_line_list(LParser::LSystem2D& systeem, Lines2D& list, img::Color color);
img::EasyImage teken_2DL(const ini::Configuration& config);

#endif
