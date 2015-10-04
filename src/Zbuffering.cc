/*****************************
 * Author: Armin Halilovic
 * Date: 5 mei 2013 - 25 mei 2013
 * Title: Zbuffering.cc
 ******************************/

#include "Zbuffering.h"
#include <limits>

double posInf = std::numeric_limits<double>::infinity();
double negInf = -std::numeric_limits<double>::infinity();
ZBuffer::ZBuffer(int width, int height):MyBuffer(width, vector<double>(height, posInf)) {}

void figures_to_lines_Zbuff(Figures3D& list3D, Lines2D& list2D) {	//A function that converts a list of figures to a list of lines.
	Line2D lijn;

	int d = 1;
	for(std::list<Figure>::iterator iter = list3D.begin(); iter != list3D.end(); ++iter) {
		for(unsigned int i = 0; i < iter->faces.size(); i++) {
			if (iter->faces[i].point_indexes.size() == 2) {			//If the "face" is just one line.
				lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[0]] , d);
				lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[1]] , d);
				lijn.color = iter->color;
				lijn.z1 = iter->points[iter->faces[i].point_indexes[0]].z;
				lijn.z2 = iter->points[iter->faces[i].point_indexes[1]].z;

				list2D.push_back(lijn);
			} else {												//If the face is at least a triangle.
				for(unsigned int j = 0; j < iter->faces[i].point_indexes.size(); j++) {		
					if (j == iter->faces[i].point_indexes.size() - 1) {
						lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[j]] , d);
						lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[0]] , d);
						lijn.z1 = iter->points[iter->faces[i].point_indexes[j]].z;
						lijn.z2 = iter->points[iter->faces[i].point_indexes[0]].z;
					} else {
						lijn.p1 = doProjection(iter->points[iter->faces[i].point_indexes[j]] , d);
						lijn.p2 = doProjection(iter->points[iter->faces[i].point_indexes[j + 1]] , d);
						lijn.z1 = iter->points[iter->faces[i].point_indexes[j]].z;
						lijn.z2 = iter->points[iter->faces[i].point_indexes[j + 1]].z;
					}
					lijn.color = iter->color;
					list2D.push_back(lijn);
				}
			}
		}
	}
}

void draw_Zbuff_line(img::EasyImage& image, ZBuffer& Z, unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, double Za, double Zb, img::Color color) {
	double p, pixelsMinEen;											//This function will draw z-buffered lines.
	double Zinverse;

	if ((x0 == x1) && (y0 == y1)) {									//Special case for drawing 1 point.
		Zinverse = 1/Za;
		if (Zinverse < Z.MyBuffer[x0][y0]) {
			Z.MyBuffer[x0][y0] = Zinverse;
			image(x0, y0) = color;
		}
	} else if (x0 == x1) {											//Special case for x0 == x1.
		if (y0 > y1) {
			swap(y0, y1);
			swap(Za, Zb);
		}
		pixelsMinEen = y1 - y0;
		for (int i = pixelsMinEen; i >= 0; i--) {
			p = i / pixelsMinEen;
			Zinverse = (p / Za) + ((1 - p) / Zb);
			unsigned int x = round_to_int((p * x0) + ((1 - p) * x1));
			unsigned int y = round_to_int((p * y0) + ((1 - p) * y1));

			if (Zinverse < Z.MyBuffer[x][y]) {
				Z.MyBuffer[x][y] = Zinverse;
				image(x, y) = color;
			}
		}
	} else if (y0 == y1) {											//Special case for y0 == y1.
		if (x0 > x1) {
			swap(x0, x1);
			swap(Za, Zb);
		}
		pixelsMinEen = x1 - x0;

		for (int i = pixelsMinEen; i >= 0; i--) {
			p = i / pixelsMinEen;
			Zinverse = (p / Za) + ((1 - p) / Zb);

			unsigned int x = round_to_int((p * x0) + ((1 - p) * x1));
			unsigned int y = round_to_int((p * y0) + ((1 - p) * y1));

			if (Zinverse < Z.MyBuffer[x][y]) {
				Z.MyBuffer[x][y] = Zinverse;
				image(x, y) = color;
			}
		}

	} else {
		if (x0 > x1) {												//Flip points if x1>x0: we want x0 to have the lowest value.
			swap(x0, x1);
			swap(y0, y1);
			swap(Za, Zb);
		}

		double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);

		if (-1.0 <= m && m <= 1.0) {
			pixelsMinEen = x1 - x0;
			for (int i = pixelsMinEen; i >= 0; i--) {
				p = i / pixelsMinEen;
				Zinverse = (p / Za) + ((1 - p)/ Zb);
				unsigned int x = round_to_int((p * x0) + ((1 - p) * x1));
				unsigned int y = round_to_int((p * y0) + ((1 - p) * y1));

				if (Zinverse < Z.MyBuffer[x][y]) {
					Z.MyBuffer[x][y] = Zinverse;
					image(x, y) = color;
				}
			}
		} else if (m > 1.0) {
			pixelsMinEen = y1 - y0;
			for (int i = pixelsMinEen; i >= 0; i--) {
				p = i / pixelsMinEen;
				Zinverse = (p / Za) + ((1 - p)/ Zb);
				unsigned int x = round_to_int((p * x0) + ((1 - p) * x1));
				unsigned int y = round_to_int((p * y0) + ((1 - p) * y1));

				if (Zinverse < Z.MyBuffer[x][y]) {
					Z.MyBuffer[x][y] = Zinverse;
					image(x, y) = color;
				}
			}
		} else if (m < -1.0) {
			pixelsMinEen = y0 - y1;
			for (int i = pixelsMinEen; i >= 0; i--) {
				p = i / pixelsMinEen;
				Zinverse = (p / Za) + ((1 - p)/ Zb);
				unsigned int x = round_to_int((p * x0) + ((1 - p) * x1));
				unsigned int y = round_to_int((p * y0) + ((1 - p) * y1));

				if (Zinverse < Z.MyBuffer[x][y]) {
					Z.MyBuffer[x][y] = Zinverse;
					image(x, y) = color;
				}
			}
		}
	}
}

img::EasyImage draw_Zbuff_linedrawing(Lines2D& lines, int size, img::Color kleur) {
	std::list<Line2D>::iterator iter;								//An iterator over the list with lines
	iter = lines.begin();

	double Xmax = std::max(iter->p1.x, iter->p2.x);					//First we take the Max and Min values of the first element in the list
	double Xmin = std::min(iter->p1.x, iter->p2.x);
	double Ymax = std::max(iter->p1.y, iter->p2.y);
	double Ymin = std::min(iter->p1.y, iter->p2.y);

	for (iter = lines.begin(); iter != lines.end(); ++iter) {		//The we use the iterator to determine the Max and Min values of all lines
		Xmax = std::max(std::max(iter->p1.x, iter->p2.x), Xmax);
		Xmin = std::min(std::min(iter->p1.x, iter->p2.x), Xmin);
		Ymax = std::max(std::max(iter->p1.y, iter->p2.y), Ymax);
		Ymin = std::min(std::min(iter->p1.y, iter->p2.y), Ymin);
	}

	double Xrange = Xmax - Xmin;
	double Yrange = Ymax - Ymin;

	double ImageX = size * (Xrange / std::max(Xrange, Yrange));		//ImageX and ImageY determine the size of the image
	double ImageY = size * (Yrange / std::max(Xrange, Yrange));

	double d = 0.95 * (ImageX / Xrange);							//A scaling factor d
	for(iter = lines.begin(); iter != lines.end(); ++iter) {		//Mutiply all coords with d to get the scale we want
		iter->p1.x *= d;
		iter->p1.y *= d;
		iter->p2.x *= d;
		iter->p2.y *= d;
	}

	double DCx = d * ((Xmin + Xmax) / 2);							//Some values to help move the picture
	double DCy = d * ((Ymin + Ymax) / 2);

	double dx = (ImageX / 2) - DCx;									//Ditto
	double dy = (ImageY / 2) - DCy;
	for(iter = lines.begin(); iter != lines.end(); ++iter) {		//Add (dx, dy) to all points, so we move te picture to its right position
		iter->p1.x += dx;
		iter->p1.y += dy;
		iter->p2.x += dx;
		iter->p2.y += dy;
	}

	ImageX = round_to_int(ImageX);									//Round the values we need to draw the picture
	ImageY = round_to_int(ImageY);
	for(iter = lines.begin(); iter != lines.end(); ++iter) {
		iter->p1.x = round_to_int(iter->p1.x);
		iter->p1.y = round_to_int(iter->p1.y);
		iter->p2.x = round_to_int(iter->p2.x);
		iter->p2.y = round_to_int(iter->p2.y);
	}

	ZBuffer Z(ImageX, ImageY);										//Initialize the z-buffer.
	img::EasyImage image(ImageX, ImageY, kleur);					//Draw the picture
	for (iter = lines.begin(); iter != lines.end(); ++iter) {
		img::Color c(iter->color.red, iter->color.green, iter->color.blue); 
		draw_Zbuff_line(image, Z, iter->p1.x, iter->p1.y, iter->p2.x, iter->p2.y, iter->z1, iter->z2, c);
	}

	return image;
}

img::EasyImage teken_ZBuff_lijntekening(const ini::Configuration& config) {
	int ImageSize = config["General"]["size"].as_int_or_die();
	int nrFigures = config["General"]["nrFigures"].as_int_or_die();
	std::vector<double> eye = config["General"]["eye"].as_double_tuple_or_die();
	std::vector<double> backgroundcolor = config["General"]["backgroundcolor"].as_double_tuple_or_die();

	Vector3D oogpunt = Vector3D::vector(eye[0], eye[1], eye[2]);
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
			cerr << "Image type of figure " << i << " was not recognised, this figure will be  skipped." << endl;
			continue;
		}

		apply_transformation(MyFigure, V, scale, rotateXangle, rotateYangle, rotateZangle, center);
		//Apply all transformations to the figure.
		ListOfFigures.push_back(MyFigure);							//Put the figure in the list of figures and create the next one.
	}

	Lines2D ListOfLines; 											//Prepare a list for lines.
	figures_to_lines_Zbuff(ListOfFigures, ListOfLines);				//Convert the list of 3Dfigures to a list of 2D lines.
	return draw_Zbuff_linedrawing(ListOfLines, ImageSize, background);//Draw the 2D lines.
}



void triangulate(Figure &MyFigure) {								//Convert all faces into triangles.
	Figure MyHelpFigure;
	Face Triangle;

	for (unsigned int i = 0; i < MyFigure.faces.size(); i++) {
		if (MyFigure.faces[i].point_indexes.size() > 3) {			//If the face has more than 3 points.
			int n = MyFigure.faces[i].point_indexes.size();
			vector<int> nHoek = MyFigure.faces[i].point_indexes;	//Create new triangles based on the type of polygon.

			for (int j = 1; j < n - 1; j++) {
				int driehoek[] = {nHoek[0], nHoek[j], nHoek[j + 1]};
				vector<int> Driehoek(driehoek, driehoek + 3);
				Triangle.point_indexes = Driehoek;
				MyHelpFigure.faces.push_back(Triangle);
			}
		} else {													//Else, just copy the face.
			MyHelpFigure.faces.push_back(MyFigure.faces[i]);
		}
	}
	MyFigure.faces = MyHelpFigure.faces;
}

void draw_colored_triang(img::EasyImage& image, Vector3D const& A, Vector3D const& B, Vector3D const& C, double dx, double dy, double d, img::Color color) {
	Point2D a, b, c;												//A function to color a triangle.
	a.x = ((d * A.x) / (-A.z)) + dx;
	a.y = ((d * A.y) / (-A.z)) + dy;
	b.x = ((d * B.x) / (-B.z)) + dx;
	b.y = ((d * B.y) / (-B.z)) + dy;
	c.x = ((d * C.x) / (-C.z)) + dx;
	c.y = ((d * C.y) / (-C.z)) + dy;

	int Ymin = round_to_int(min(min(a.y, b.y), c.y) + 0.5);			//Find the minimal and maxmal Y values.
	int Ymax = round_to_int(max(max(a.y, b.y), c.y) - 0.5);

	for (int y = Ymin; y <= Ymax; y++) {							//Then for each Y value, find Xmin and Xmax.
		double XlAB = posInf, XlAC = posInf, XlBC = posInf;
		double XrAB = negInf, XrAC = negInf, XrBC = negInf;

		if (((y - a.y) * (y - b.y)) <= 0 and a.y != b.y) {			//Check AB
			XlAB = a.x + (((b.x - a.x) * (y - a.y)) / (b.y - a.y));
			XrAB = a.x + (((b.x - a.x) * (y - a.y)) / (b.y - a.y));
		}

		if (((y - b.y) * (y - c.y)) <= 0 and b.y != c.y) {			//Check BC
			XlBC = b.x + (((c.x - b.x) * (y - b.y)) / (c.y - b.y));
			XrBC = b.x + (((c.x - b.x) * (y - b.y)) / (c.y - b.y));
		}

		if (((y - a.y) * (y - c.y)) <= 0 and a.y != c.y) {			//Check AC
			XlAC = a.x + (((c.x - a.x) * (y - a.y)) / (c.y - a.y));
			XrAC = a.x + (((c.x - a.x) * (y - a.y)) / (c.y - a.y));
		}

		int Xl = round_to_int(min(min(XlAB, XlBC), XlAC) + 0.5);
		int Xr = round_to_int(max(max(XrAB, XrBC), XrAC) - 0.5);

		for (int x = Xl; x <= Xr; x++) {
			image(x, y) = color;									//Color each pixel from left to right.
		}
	}
}

void draw_zbuf_triang(img::EasyImage& image, ZBuffer& Z, Vector3D const& A, Vector3D const& B, Vector3D const& C, double dx, double dy, double d, img::Color color) {
	Point2D a, b, c;												//A function to draw z-buffered triangles.
	a.x = ((d * A.x) / (-A.z)) + dx;
	a.y = ((d * A.y) / (-A.z)) + dy;
	b.x = ((d * B.x) / (-B.z)) + dx;
	b.y = ((d * B.y) / (-B.z)) + dy;
	c.x = ((d * C.x) / (-C.z)) + dx;
	c.y = ((d * C.y) / (-C.z)) + dy;

	int Ymin = round_to_int(min(min(a.y, b.y), c.y) + 0.5);
	int Ymax = round_to_int(max(max(a.y, b.y), c.y) - 0.5);

	double XlAB = posInf, XlAC = posInf, XlBC = posInf;
	double XrAB = negInf, XrAC = negInf, XrBC = negInf;

	double Xg = (a.x + b.x + c.x) / 3;
	double Yg = (a.y + b.y + c.y) / 3;
	double InvZg = (1 / (3 * A.z)) + (1 / (3 * B.z)) + (1 / (3 * C.z));
	double InvZ;

	Vector3D u = Vector3D::vector(B - A);
	Vector3D v = Vector3D::vector(C - A);
	Vector3D w;

	w.x = u.y * v.z - u.z * v.y;
	w.y = u.z * v.x - u.x * v.z;
	w.z = u.x * v.y - u.y * v.x;

	double k = (w.x * A.x) + (w.y * A.y) + (w.z * A.z);

	double dzdx = w.x / (-d * k);
	double dzdy = w.y / (-d * k);

	for (int y = Ymin; y <= Ymax; y++) {
		if (((y - a.y) * (y - b.y)) <= 0 and a.y != b.y) {			//Check AB
			XlAB = a.x + (((b.x - a.x) * (y - a.y)) / (b.y - a.y));
			XrAB = a.x + (((b.x - a.x) * (y - a.y)) / (b.y - a.y));
		}

		if (((y - b.y) * (y - c.y)) <= 0 and b.y != c.y) {			//Check BC
			XlBC = b.x + (((c.x - b.x) * (y - b.y)) / (c.y - b.y));
			XrBC = b.x + (((c.x - b.x) * (y - b.y)) / (c.y - b.y));
		}

		if (((y - a.y) * (y - c.y)) <= 0 and a.y != c.y) {			//Check AC
			XlAC = a.x + (((c.x - a.x) * (y - a.y)) / (c.y - a.y));
			XrAC = a.x + (((c.x - a.x) * (y - a.y)) / (c.y - a.y));
		}

		int Xl = round_to_int(min(min(XlAB, XlBC), XlAC) + 0.5);
		int Xr = round_to_int(max(max(XrAB, XrBC), XrAC) - 0.5);

		for (int x = Xl; x <= Xr; x++) {
			InvZ = (1.0001 * InvZg) + ((x - Xg) * dzdx) + ((y - Yg) * dzdy);
			if (InvZ < Z.MyBuffer[x][y]) {
				Z.MyBuffer[x][y] = InvZ;
				image(x, y) = color;
			}
		}
		XlAB = posInf, XlAC = posInf, XlBC = posInf;
		XrAB = negInf, XrAC = negInf, XrBC = negInf;
	}
}

img::EasyImage draw_Zbuff_drawing(Figures3D& ListOfFigures, int ImageSize, img::Color backgroundColor) {
	Lines2D listOfLines;
	figures_to_lines_Zbuff(ListOfFigures, listOfLines);

	std::list<Line2D>::iterator iter;								//An iterator over the list with lines
	iter = listOfLines.begin();

	double Xmax = std::max(iter->p1.x, iter->p2.x);					//First we take the Max and Min values of the first element in the list
	double Xmin = std::min(iter->p1.x, iter->p2.x);
	double Ymax = std::max(iter->p1.y, iter->p2.y);
	double Ymin = std::min(iter->p1.y, iter->p2.y);

	for (iter = listOfLines.begin(); iter != listOfLines.end(); ++iter) {//The we use the iterator to determine the Max and Min values of all lines
		Xmax = std::max(std::max(iter->p1.x, iter->p2.x), Xmax);
		Xmin = std::min(std::min(iter->p1.x, iter->p2.x), Xmin);
		Ymax = std::max(std::max(iter->p1.y, iter->p2.y), Ymax);
		Ymin = std::min(std::min(iter->p1.y, iter->p2.y), Ymin);
	}

	double Xrange = Xmax - Xmin;
	double Yrange = Ymax - Ymin;
	double ImageX = ImageSize * (Xrange / std::max(Xrange, Yrange));//ImageX and ImageY determine the size of the image
	double ImageY = ImageSize * (Yrange / std::max(Xrange, Yrange));

	double d = 0.95 * (ImageX / Xrange);							//A scaling factor d
	for(iter = listOfLines.begin(); iter != listOfLines.end(); ++iter) {//Mutiply all coords with d to get the scale we want
		iter->p1.x *= d;
		iter->p1.y *= d;
		iter->p2.x *= d;
		iter->p2.y *= d;
	}

	double DCx = d * ((Xmin + Xmax) / 2);							//Some values to help move the picture
	double DCy = d * ((Ymin + Ymax) / 2);
	double dx = (ImageX / 2) - DCx;									//Ditto
	double dy = (ImageY / 2) - DCy;

	for(iter = listOfLines.begin(); iter != listOfLines.end(); ++iter) {//Add (dx, dy) to all points, so we move te picture to its right position
		iter->p1.x += dx;
		iter->p1.y += dy;
		iter->p2.x += dx;
		iter->p2.y += dy;
	}

	ImageX = round_to_int(ImageX);									//Round the values we need to draw the picture
	ImageY = round_to_int(ImageY);
	for(iter = listOfLines.begin(); iter != listOfLines.end(); ++iter) {
		iter->p1.x = round_to_int(iter->p1.x);
		iter->p1.y = round_to_int(iter->p1.y);
		iter->p2.x = round_to_int(iter->p2.x);
		iter->p2.y = round_to_int(iter->p2.y);
	}

	ZBuffer Z(ImageX, ImageY);										//Initialize the z-buffer.
	img::EasyImage image(ImageX, ImageY, backgroundColor);			//Draw the picture
	for (list<Figure>::iterator it = ListOfFigures.begin(); it != ListOfFigures.end(); it++) {
		img::Color c(it->color.red, it->color.green, it->color.blue);
		bool triangulated = false;

		for (unsigned int derp = 0; derp < it->faces.size(); derp++) {
			if (it->faces[derp].point_indexes.size() > 2) {
				triangulated = true;
			}
		}

		if (triangulated) {
			for (unsigned int i = 0; i < it->faces.size(); i++) {		//For each face, which should be a triangle, draw the the face.
				Vector3D A = it->points[it->faces[i].point_indexes[0]];
				Vector3D B = it->points[it->faces[i].point_indexes[1]];
				Vector3D C = it->points[it->faces[i].point_indexes[2]];
				draw_zbuf_triang(image, Z, A, B, C, dx, dy, d, c);
			}
		} else {														//For a 3DL system, or 3D linedrawing.
			for (iter = listOfLines.begin(); iter != listOfLines.end(); ++iter) {
				draw_Zbuff_line(image, Z, iter->p1.x, iter->p1.y, iter->p2.x, iter->p2.y, iter->z1, iter->z2, c);
			}
		}
	}

	return image;
}

img::EasyImage teken_ZBuff_tekening(const ini::Configuration& config)  {
	int ImageSize = config["General"]["size"].as_int_or_die();
	int nrFigures = config["General"]["nrFigures"].as_int_or_die();
	std::vector<double> eye = config["General"]["eye"].as_double_tuple_or_die();
	std::vector<double> backgroundcolor = config["General"]["backgroundcolor"].as_double_tuple_or_die();

	Vector3D oogpunt = Vector3D::vector(eye[0], eye[1], eye[2]);
	to_polar(oogpunt);
	Matrix V = eyePoint_trans(oogpunt);									//Create the eyepoint matrix V to see figures from the right angle.
	img::Color background(backgroundcolor[0] * 255, backgroundcolor[1] * 255, backgroundcolor[2] * 255);

	Figures3D ListOfFigures;											//Prepare a list for the figures.

	for (int i = 0; i < nrFigures; i++) {								//Loop over the amount of figures to be made.
		stringstream figureNr;											//Use a stringstream to read several figures' information.
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
		Figure MyFigure;												//Prepare a figure and give it a color.
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

		} else {														//If the figure is not recognised, skip it.
			std::cerr << "Image type of figure " << i << " was not recognised, this figure will be  skipped." << std::endl;
		}

		apply_transformation(MyFigure, V, scale, rotateXangle, rotateYangle, rotateZangle, center);
		//Apply all transformations to the figure.
		triangulate(MyFigure);											//Turn all faces into triangles.
		ListOfFigures.push_back(MyFigure);								//Put the figure in the list of figures and create the next one.
	}

	return draw_Zbuff_drawing(ListOfFigures, ImageSize, background);	//Draw the triangles.
}
