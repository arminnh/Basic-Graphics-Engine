/*****************************
* Author: Armin Halilovic
* Date: 5 mei 2013 - 25 mei 2013
* Title: Zbuffering.h
******************************/

#include "3Dlines.h"
#include "3Dbodies.h"
#include "3Dlines.h"

#ifndef ZBUFF_H_
#define ZBUFF_H_
		
class ZBuffer {
 public:
	vector<vector<double> > MyBuffer;
	ZBuffer(int width, int height);
};

void figures_to_lines_Zbuff(Figures3D& list3D, Lines2D& list2D);
void draw_Zbuff_line(img::EasyImage& image, ZBuffer& ZBuffer, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, double Za, double Zb, img::Color color);
img::EasyImage draw_Zbuff_lines(Lines2D& lines, int size, img::Color kleur);
img::EasyImage teken_ZBuff_lijntekening(const ini::Configuration& config);

void triangulate(Figure &MyFigure);
void draw_colored_triang(img::EasyImage& image, Vector3D const& A, Vector3D const& B, Vector3D const& C, double dx, double dy, double d, Color color);
void draw_zbuf_triag(img::EasyImage& image, ZBuffer& Z, Vector3D const& A, Vector3D const& B, Vector3D const& C, double d, double dx, double dy, Color color);
img::EasyImage draw_Zbuff_drawing(Figures3D& lines, int size, img::Color kleur);
img::EasyImage teken_ZBuff_tekening(const ini::Configuration& config);

#endif
