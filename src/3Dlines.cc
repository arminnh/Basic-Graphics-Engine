/****************************************
* Author: Armin Halilovic
* Date: 26 februari 2013 - 8 maart 2013 
* Title: 3D lines.cc
*****************************************/

#include "3Dlines.h"
#include "3Dbodies.h"
#include "Zbuffering.h"

Matrix scale_figure(double scale) {									//A matrix to scale the figure.
	Matrix S;
	S(1, 1) = scale;
	S(2, 2) = scale;
	S(3, 3) = scale;
	S(4, 4) = 1;
	return S;
}

Matrix rotateX(double angle) {										//A matrix to rotate the figure around the X-axis.
	Matrix X;
	X(1, 1) = 1;
	X(2, 2) = cos(angle);
	X(2, 3) = sin(angle);
	X(3, 2) = -sin(angle);
	X(3, 3) = cos(angle);
	X(4, 4) = 1;
	return X;
}

Matrix rotateY(double angle) {										//A matrix to rotate the figure around the Y-axis.
	Matrix Y;
	Y(1, 1) = cos(angle);
	Y(1, 3) = -sin(angle);
	Y(2, 2) = 1;
	Y(3, 1) = sin(angle);
	Y(3, 3) = cos(angle);
	Y(4, 4) = 1;
	return Y;
}

Matrix rotateZ(double angle) {										//A matrix to rotate the figure around the Z-axis.
	Matrix Z;
	Z(1, 1) = cos(angle);
	Z(1, 2) = sin(angle);
	Z(2, 1) = -sin(angle);
	Z(2, 2) = cos(angle);
	Z(3, 3) = 1;
	Z(4, 4) = 1;
	return Z;
}

Matrix translate(Vector3D vector) {									//A matrix to move the figure to its right position.
	Matrix trans;
	trans(1, 1) = 1;
	trans(2, 2) = 1;
	trans(3, 3) = 1;
	trans(4, 4) = 1;
	trans(4, 1) = vector.x;
	trans(4, 2) = vector.y;
	trans(4, 3) = vector.z;
	return trans;
}

Matrix eyePoint_trans(Vector3D eyepoint) {							//The eyepoint matrix, which will help us view the picture from a desired angle.
	Matrix v;
	v(1, 1) = -(sin(eyepoint.y));
	v(1, 2) = -(cos(eyepoint.y) * cos(eyepoint.z));
	v(1, 3) = (cos(eyepoint.y) * sin(eyepoint.z));
	v(2, 1) = (cos(eyepoint.y));
	v(2, 2) = -(sin(eyepoint.y) * cos(eyepoint.z));
	v(2, 3) = (sin(eyepoint.y) * sin(eyepoint.z));
	v(3, 2) = (sin(eyepoint.z));
	v(3, 3) = (cos(eyepoint.z));
	v(4, 3) = -(eyepoint.x);
	v(4, 4) = 1;
	return v;
}

																	//A function that will multiply all points in a figure by the matrices above.
void apply_transformation(Figure& figure, Matrix const& Eye, double scale, double rotateXangle, double rotateYangle, double rotateZangle, Vector3D center) {
	Matrix Ms = scale_figure(scale);
	Matrix Mx = rotateX(rotateXangle);
	Matrix My = rotateY(rotateYangle);
	Matrix Mz = rotateZ(rotateZangle);
	Matrix Mt = translate(center);
	
	Matrix Everything = Ms * Mx * My * Mz * Mt * Eye;
	
	for(unsigned int i = 0; i < figure.points.size() ; i++) {
		figure.points[i] = figure.points[i] * Everything;
	}
}

void to_polar(Vector3D& point) {									//A function to convert rectangular coordinates to polar ones, nessecary for the eyepoint matrix.
	double r = sqrt((pow(point.x, 2)) + (pow(point.y, 2)) + (pow(point.z, 2)));
	double theta = atan2(point.y, point.x);
	double phi = acos(point.z / r);
	
	point.x = r;
	point.y = theta;
	point.z = phi;
}

Point2D doProjection(Vector3D point, double d) {					//A function that converts Vector3D points to Point2D points.
	Point2D punt;
	
	punt.x = ((d * point.x) / (-point.z));
	punt.y = ((d * point.y) / (-point.z));
	
	return punt;
}

void figures_to_lines(Figures3D& list3D, Lines2D& list2D) {			//A function that converts a list of figures to a list of lines.
	Line2D lijn;
	
	int d = 1;
	for(std::list<Figure>::iterator iter = list3D.begin(); iter != list3D.end(); ++iter) {
		for(unsigned int i = 0; i < iter->faces.size(); i++) {
			if (iter->faces[i].point_indexes.size() == 2) {			//If the "face" is just one line.
			 	lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[0]] , d);
				lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[1]] , d);
				lijn.color = iter->color;
				list2D.push_back(lijn);
			} else {												//If the face is at least a triangle.
				for(unsigned int j = 0; j < iter->faces[i].point_indexes.size(); j++) {		
					if (j == iter->faces[i].point_indexes.size() - 1) {
						//For the last line, connect the last point to the first one.
						lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[j]] , d);
						lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[0]] , d);
					} else {
						lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[j]] , d);
						lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[j + 1]] , d);
					}
					lijn.color = iter->color;
					list2D.push_back(lijn);
				}
			}
		}
	}
}

img::EasyImage teken_3D_lijntekening(const ini::Configuration& config) {
	int ImageSize = config["General"]["size"].as_int_or_die();
	int nrFigures = config["General"]["nrFigures"].as_int_or_die();
	std::vector<double> eye = config["General"]["eye"].as_double_tuple_or_die();
	std::vector<double> backgroundcolor = config["General"]["backgroundcolor"].as_double_tuple_or_die();
	
	Vector3D oogpunt = Vector3D::vector(eye[0], eye[1], eye[2]);	//The angle from which you see the picture.
	to_polar(oogpunt);
	Matrix V = eyePoint_trans(oogpunt);								//Create the eyepoint matrix V to see figures from the right angle.
	img::Color background(backgroundcolor[0] * 255, backgroundcolor[1] * 255, backgroundcolor[2] * 255);

	Figures3D ListOfFigures;										//Prepare a list for the figures.
	
	for (int i = 0; i < nrFigures; i++) {							//Loop over the amount of figures to be made.
		stringstream figureNr;										//Use a stringstream to read several figures' information.
		figureNr << "Figure" << i;
		std::string figuretype = config[figureNr.str()]["type"].as_string_or_die();
		double scale = config[figureNr.str()]["scale"].as_double_or_die();
		double rotateXangle = config[figureNr.str()]["rotateX"].as_double_or_die();
		double rotateYangle = config[figureNr.str()]["rotateY"].as_double_or_die();
		double rotateZangle = config[figureNr.str()]["rotateZ"].as_double_or_die();
		std::vector<double> FigCenter = config[figureNr.str()]["center"].as_double_tuple_or_die();
		std::vector<double> linecolor = config[figureNr.str()]["color"].as_double_tuple_or_die();

		rotateXangle *= (PI / 180);
		rotateYangle *= (PI / 180);
		rotateZangle *= (PI / 180);

		Vector3D center = Vector3D::vector(FigCenter[0], FigCenter[1], FigCenter[2]);
																	//A vector to move the image over to the center.			
		Figure MyFigure;											//Prepare a figure and give it a color.		
		MyFigure.color.red = linecolor[0] * 255;
		MyFigure.color.green = linecolor[1] * 255;
		MyFigure.color.blue = linecolor[2] * 255;
																	//Create a figure based on the figuretype recieved.
		if (figuretype == "LineDrawing") {
			int nrLines = config[figureNr.str()]["nrLines"].as_int_or_die();
			int nrPoints = config[figureNr.str()]["nrPoints"].as_int_or_die();
			createLineDrawing(MyFigure, config, figureNr, nrLines, nrPoints);

		} else if (figuretype == "Cube") {
			createCube(MyFigure);
			
		} else if (figuretype == "Tetrahedron") {
			createTetrahedron(MyFigure);
			
		} else if (figuretype == "Octahedron") {
			createOctahedron(MyFigure);
			
		} else if (figuretype == "Icosahedron") {
			createIcosahedron(MyFigure);
			
		} else if (figuretype == "Dodecahedron") {
			createDodecahedron(MyFigure);
			
		} else if (figuretype ==  "Cylinder") {
			int n = config[figureNr.str()]["n"].as_int_or_die();
			double height = config[figureNr.str()]["height"].as_double_or_die();
			createCylinder(MyFigure, n, height);
			
		} else if (figuretype == "Cone") {
			int n = config[figureNr.str()]["n"].as_int_or_die();
			double height = config[figureNr.str()]["height"].as_double_or_die();
			createCone(MyFigure, n, height);
			
		} else if (figuretype == "Sphere") {
			int n = config[figureNr.str()]["n"].as_int_or_die();
			createSphere(MyFigure, n);
			
		} else if (figuretype == "Torus") {
			int m = config[figureNr.str()]["m"].as_int_or_die();
			int n = config[figureNr.str()]["n"].as_int_or_die();
			double r = config[figureNr.str()]["r"].as_double_or_die();
			double R = config[figureNr.str()]["R"].as_double_or_die();
			createTorus(MyFigure, m, n, r, R);
			
		} else if (figuretype == "3DLSystem") {
			string input = config[figureNr.str()]["inputfile"].as_string_or_die();
			create3DLSystem(MyFigure, input);
			
		} else {													//If the figure is not recognised, skip it.
			std::cerr << "Image type of figure " << i << " was not recognised, this figure will be  skipped." << std::endl;
		}
		
		apply_transformation(MyFigure, V, scale, rotateXangle, rotateYangle, rotateZangle, center);
																	//Apply all transformations to the figure.
		ListOfFigures.push_back(MyFigure);							//Put the figure in the list of figures and create the next one.
	}
	
	Lines2D ListOfLines; 											//Prepare a list for lines.
	figures_to_lines(ListOfFigures, ListOfLines);					//Convert the list of 3Dfigures to a list of 2D lines.
	return draw_2D_lines(ListOfLines, ImageSize, background);		//Draw the 2D lines.
}
