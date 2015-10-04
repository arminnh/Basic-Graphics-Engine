/*****************************
* Author: Armin Halilovic
* Date: 2 mei 2013 - 3 mei 2013
* Title: 3Dbodies.h
******************************/

#include "3Dlines.h"

#ifndef B3D_H_
#define B3D_H_

void createLineDrawing(Figure &MyFigure, const ini::Configuration& config, stringstream &figureNr, unsigned int nrLines, unsigned int nrPoints);
void createCube(Figure &MyFigure);
void createTetrahedron(Figure &MyFigure);
void createOctahedron(Figure &MyFigure);
void createIcosahedron(Figure &MyFigure);
void createDodecahedron(Figure &MyFigure);
void createSphere(Figure &MyFigure, unsigned int n);
void createCylinder(Figure &MyFigure, unsigned int n, double height);
void createCone(Figure &MyFigure, unsigned int n, double height);
void createTorus(Figure &MyFigure, unsigned int m, unsigned int n, double r, double R);
void create3DLSystem(Figure &MyFigure, string input);

#endif
