/*****************************
* Author: Armin Halilovic
* Date: 26 februari 2013 - 8 maart 2013 
* Title: 3D lines.h
******************************/

#include "2Dlines.h"

#ifndef L3D_H_
#define L3D_H_

class Face {
  public:							//De indexen refereren naar punten in de ‘points’ vector van de Figure-klasse	
	std::vector<int> point_indexes;
};

class Figure {
  public:
	std::vector<Vector3D> points;
	std::vector<Face> faces;
	Color color;
};

typedef std::list<Figure> Figures3D;

Matrix scale_figure(double scale);
Matrix rotateX(double angle);
Matrix rotateY(double angle);
Matrix rotateZ(double angle);
Matrix translate(Vector3D vector);
Matrix eyePoint_trans(Vector3D eyepoint);
void apply_transformation(Figure& figure, Matrix const& Eye, double scale, double rotateXangle, double rotateYangle, double rotateZangle, Vector3D vector);
void to_polar(Vector3D& point);
Point2D doProjection(Vector3D point, double d);
void figures_to_lines(Figures3D& list3D, Lines2D& list2D);
void pushLineDrawing(const ini::Configuration &config, stringstream &figure, Figures3D &ListOfFigures, Matrix V);
img::EasyImage teken_3D_lijntekening(const ini::Configuration& config);

#endif 
