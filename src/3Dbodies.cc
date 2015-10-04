/*****************************
 * Author: Armin Halilovic
 * Date: 2 mei 2013 - 3 mei 2013
 * Title: 3Dbodies.cc
 ******************************/

#include "3Dbodies.h"

void createLineDrawing(Figure &MyFigure, const ini::Configuration& config, stringstream &figureNr, unsigned int nrLines, unsigned int nrPoints) {
	for (unsigned int j = 0; j < nrPoints; j++) {					//Read the points out of the file into the figure.
		stringstream point;											//Use a stringstream to read several points.
		point << "point" << j;
		std::vector<double> IniPoint = config[figureNr.str()][point.str()].as_double_tuple_or_die();

		Vector3D a = Vector3D::point(IniPoint[0], IniPoint[1], IniPoint[2]);
		//Use the given Vector3D::point class and convert the point out of the ini file to this point.
		MyFigure.points.push_back(a);								//Put the points in the figure.
	}

	Face FaceLines;													//The class Face will be used to put the lines of faces in the Figure MyFigure.
	for (unsigned int k = 0; k < nrLines; k++) {					//Read the lines out of the file into the figure.
		stringstream linee;											//Use a stringstream to read several lines.
		linee << "line" << k;
		FaceLines.point_indexes = config[figureNr.str()][linee.str()].as_int_tuple_or_die();

		MyFigure.faces.push_back(FaceLines);						//Put the (Face) line in the figure.
	}
}

void createCube(Figure &MyFigure) {
	MyFigure.points.push_back(Vector3D::point(1, -1, -1));			//Create the points of a cube.
	MyFigure.points.push_back(Vector3D::point(-1, 1, -1));
	MyFigure.points.push_back(Vector3D::point(1, 1, 1));
	MyFigure.points.push_back(Vector3D::point(-1, -1, 1));
	MyFigure.points.push_back(Vector3D::point(1, 1, -1));
	MyFigure.points.push_back(Vector3D::point(-1, -1, -1));
	MyFigure.points.push_back(Vector3D::point(1, -1, 1));
	MyFigure.points.push_back(Vector3D::point(-1, 1, 1));

	int een[] = {0, 4, 2, 6};										//Create several faces using the created points.
	int twee[] = {4, 1, 7, 2};
	int drie[] = {1, 5, 3, 7};
	int vier[] = {5, 0, 6, 3};
	int vijf[] = {6, 2, 7, 3};
	int zes[] = {0, 5, 1, 4};
	std::vector<int> Een(een, een + 4);
	std::vector<int> Twee(twee, twee + 4);
	std::vector<int> Drie(drie, drie + 4);
	std::vector<int> Vier(vier, vier + 4);
	std::vector<int> Vijf(vijf, vijf + 4);
	std::vector<int> Zes(zes, zes + 4);
	Face FaceLines;
	FaceLines.point_indexes = Een;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twee;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Drie;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vier;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vijf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zes;
	MyFigure.faces.push_back(FaceLines);
}

void createTetrahedron(Figure &MyFigure) {
	MyFigure.points.push_back(Vector3D::point(1, -1, -1));			//Create the points of a tetrahedron.
	MyFigure.points.push_back(Vector3D::point(-1, 1, -1));
	MyFigure.points.push_back(Vector3D::point(1, 1, 1));
	MyFigure.points.push_back(Vector3D::point(-1, -1, 1));

	int een[] = {0, 1, 2};											//Create several faces using the created points.
	int twee[] = {1, 3, 2};
	int drie[] = {0, 3, 1};
	int vier[] = {0, 2, 3};
	std::vector<int> Een(een, een + 3);
	std::vector<int> Twee(twee, twee + 3);
	std::vector<int> Drie(drie, drie + 3);
	std::vector<int> Vier(vier, vier + 3);
	Face FaceLines;
	FaceLines.point_indexes = Een;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twee;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Drie;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vier;
	MyFigure.faces.push_back(FaceLines);
}

void createOctahedron(Figure &MyFigure) {
	MyFigure.points.push_back(Vector3D::point(1, 0, 0));			//Create the points of an octahedron.
	MyFigure.points.push_back(Vector3D::point(0, 1, 0));
	MyFigure.points.push_back(Vector3D::point(-1, 0, 0));
	MyFigure.points.push_back(Vector3D::point(0, -1, 0));
	MyFigure.points.push_back(Vector3D::point(0, 0, -1));
	MyFigure.points.push_back(Vector3D::point(0, 0, 1));

	int een[] = {0, 1, 5};											//Create several faces using the created points.
	int twee[] = {1, 2, 5};
	int drie[] = {2, 3, 5};
	int vier[] = {3, 0, 5};
	int vijf[] = {1, 0, 4};
	int zes[] = {2, 1, 4};
	int zeven[] = {3, 2, 4};
	int acht[] = {0, 3, 4};
	std::vector<int> Een(een, een + 3);
	std::vector<int> Twee(twee, twee + 3);
	std::vector<int> Drie(drie, drie + 3);
	std::vector<int> Vier(vier, vier + 3);
	std::vector<int> Vijf(vijf, vijf + 3);
	std::vector<int> Zes(zes, zes + 3);
	std::vector<int> Zeven(zeven, zeven + 3);
	std::vector<int> Acht(acht, acht + 3);
	Face FaceLines;
	FaceLines.point_indexes = Een;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twee;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Drie;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vier;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vijf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zes;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zeven;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Acht;
	MyFigure.faces.push_back(FaceLines);
}

void createIcosahedron(Figure &MyFigure) {
	MyFigure.points.push_back(Vector3D::point(0, 0, (sqrt(5) / 2)));//Create the points of an icosahedron.
	for (unsigned int i = 2; i <= 6; i++) {
		MyFigure.points.push_back(Vector3D::point(cos(((i - 2) * 2 * PI) / 5), sin(((i - 2) * 2 * PI) / 5), 0.5));
	}

	for (unsigned int i = 7; i <= 11; i++) {
		MyFigure.points.push_back(Vector3D::point(cos((PI / 5) + ((i - 7) * 2 * PI) / 5), sin((PI / 5) + ((i - 7) * 2 * PI) / 5), -0.5));
	}
	MyFigure.points.push_back(Vector3D::point(0, 0, -(sqrt(5) / 2)));

	int een[] = {0, 1, 2};											//Create several faces using the created points.
	int twee[] = {0, 2, 3};
	int drie[] = {0, 3, 4};
	int vier[] = {0, 4, 5};
	int vijf[] = {0, 5, 1};
	int zes[] = {1, 6, 2};
	int zeven[] = {2, 6, 7};
	int acht[] = {2, 7, 3};
	int negen[] = {3, 7, 8};
	int tien[] = {3, 8, 4};
	int elf[] = {4, 8, 9};
	int twaalf[] = {4, 9, 5};
	int dertien[] = {5, 9, 10};
	int veertien[] = {5, 10, 1};
	int vijftien[] = {1, 10, 6};
	int zestien[] = {11, 7, 6};
	int zeventien[] = {11, 8, 7};
	int achttien[] = {11, 9, 8};
	int negentien[] = {11, 10, 9};
	int twintig[] = {11, 6, 10};
	std::vector<int> Een(een, een + 3);
	std::vector<int> Twee(twee, twee + 3);
	std::vector<int> Drie(drie, drie + 3);
	std::vector<int> Vier(vier, vier + 3);
	std::vector<int> Vijf(vijf, vijf + 3);
	std::vector<int> Zes(zes, zes + 3);
	std::vector<int> Zeven(zeven, zeven + 3);
	std::vector<int> Acht(acht, acht + 3);
	std::vector<int> Negen(negen, negen + 3);
	std::vector<int> Tien(tien, tien + 3);
	std::vector<int> Elf(elf, elf + 3);
	std::vector<int> Twaalf(twaalf, twaalf + 3);
	std::vector<int> Dertien(dertien, dertien + 3);
	std::vector<int> Veertien(veertien, veertien + 3);
	std::vector<int> Vijftien(vijftien, vijftien + 3);
	std::vector<int> Zestien(zestien, zestien + 3);
	std::vector<int> Zeventien(zeventien, zeventien + 3);
	std::vector<int> Achttien(achttien, achttien + 3);
	std::vector<int> Negentien(negentien, negentien + 3);
	std::vector<int> Twintig(twintig, twintig + 3);
	Face FaceLines;
	FaceLines.point_indexes = Een;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twee;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Drie;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vier;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vijf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zes;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zeven;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Acht;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Negen;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Tien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Elf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twaalf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Dertien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Veertien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vijftien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zestien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zeventien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Achttien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Negentien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twintig;
	MyFigure.faces.push_back(FaceLines);
}

void createDodecahedron(Figure &MyFigure) {
	std::vector<Vector3D> Pts;										//Create the points of an icosahedron.
	Pts.push_back(Vector3D::point(0, 0, (sqrt(5) / 2)));
	for (unsigned int i = 2; i <= 6; i++) {
		Pts.push_back(Vector3D::point(cos(((i - 2) * 2 * PI) / 5), sin(((i - 2) * 2 * PI) / 5), 0.5));
	}

	for (unsigned int i = 7; i <= 11; i++) {
		Pts.push_back(Vector3D::point(cos((PI / 5) + ((i - 7) * 2 * PI) / 5), sin((PI / 5) + ((i - 7) * 2 * PI) / 5), -0.5));
	}
	Pts.push_back(Vector3D::point(0, 0, -(sqrt(5) / 2)));
	//Using the icosahedron-points, create new ones for a dodecahedron.
	MyFigure.points.push_back(Vector3D::point((Pts[0] + Pts[1] + Pts[2]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[0] + Pts[2] + Pts[3]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[0] + Pts[3] + Pts[4]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[0] + Pts[4] + Pts[5]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[0] + Pts[5] + Pts[1]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[1] + Pts[6] + Pts[2]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[2] + Pts[6] + Pts[7]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[2] + Pts[7] + Pts[3]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[3] + Pts[7] + Pts[8]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[3] + Pts[8] + Pts[4]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[4] + Pts[8] + Pts[9]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[4] + Pts[9] + Pts[5]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[5] + Pts[9] + Pts[10]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[5] + Pts[10] + Pts[1]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[1] + Pts[10] + Pts[6]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[11] + Pts[7] + Pts[6]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[11] + Pts[8] + Pts[7]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[11] + Pts[9] + Pts[8]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[11] + Pts[10] + Pts[9]) / 3));
	MyFigure.points.push_back(Vector3D::point((Pts[11] + Pts[6] + Pts[10]) / 3));
	Pts.clear();

	int een[] = {0, 1, 2, 3, 4};
	int twee[] = {0, 5, 6, 7, 1};
	int drie[] = {1, 7, 8, 9, 2};
	int vier[] = {2, 9, 10, 11, 3};
	int vijf[] = {3, 11, 12, 13, 4};
	int zes[] = {4, 13, 14, 5, 0};
	int zeven[] = {19, 18, 17, 16, 15};
	int acht[] = {19, 14, 13, 12, 18};
	int negen[] = {18, 12, 11, 10, 17};
	int tien[] = {17, 10, 9, 8, 16};
	int elf[] = {16, 8, 7, 6, 15};
	int twaalf[] = {15, 6, 5, 14, 19};
	std::vector<int> Een(een, een + 5);
	std::vector<int> Twee(twee, twee + 5);
	std::vector<int> Drie(drie, drie + 5);
	std::vector<int> Vier(vier, vier + 5);
	std::vector<int> Vijf(vijf, vijf + 5);
	std::vector<int> Zes(zes, zes + 5);
	std::vector<int> Zeven(zeven, zeven + 5);
	std::vector<int> Acht(acht, acht + 5);
	std::vector<int> Negen(negen, negen + 5);
	std::vector<int> Tien(tien, tien + 5);
	std::vector<int> Elf(elf, elf + 5);
	std::vector<int> Twaalf(twaalf, twaalf + 5);
	Face FaceLines;
	FaceLines.point_indexes = Een;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twee;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Drie;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vier;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Vijf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zes;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Zeven;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Acht;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Negen;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Tien;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Elf;
	MyFigure.faces.push_back(FaceLines);
	FaceLines.point_indexes = Twaalf;
}

void createSphere(Figure &MyFigure, unsigned  int n) {
	createIcosahedron(MyFigure);									//Start by creating an icosahedron
	Figure MyFigure2;
	MyFigure2.color = MyFigure.color;
	Face FaceLines;

	for (unsigned int i = 0; i < n; i++) {							//Divide each of its triangles into 4 smaller ones.
		MyFigure2.points = MyFigure.points;

		for (unsigned int j = 0; j < MyFigure.faces.size(); j++) {
			unsigned int FacePuntA = MyFigure.faces[j].point_indexes[0];//First, find the points of a triangle.
			unsigned int FacePuntB = MyFigure.faces[j].point_indexes[1];
			unsigned int FacePuntC = MyFigure.faces[j].point_indexes[2];

			Vector3D A = MyFigure2.points[FacePuntA];				//Then, create 3 new points for the new triangles.
			Vector3D B = MyFigure2.points[FacePuntB];
			Vector3D C = MyFigure2.points[FacePuntC];
			Vector3D D = Vector3D::point(((A.x + B.x) / 2), ((A.y + B.y) / 2), ((A.z + B.z) / 2));
			Vector3D E = Vector3D::point(((A.x + C.x) / 2), ((A.y + C.y) / 2), ((A.z + C.z) / 2));
			Vector3D F = Vector3D::point(((B.x + C.x) / 2), ((B.y + C.y) / 2), ((B.z + C.z) / 2));

			MyFigure2.points.push_back(D);
			MyFigure2.points.push_back(E);
			MyFigure2.points.push_back(F);
			//Then, using all 6 points, create 4 faces (triangles).
			unsigned int een[] = {FacePuntA, MyFigure2.points.size() - 3, MyFigure2.points.size() - 2};
			unsigned int twee[] = {FacePuntB, MyFigure2.points.size() - 1, MyFigure2.points.size() - 3};
			unsigned int drie[] = {FacePuntC, MyFigure2.points.size() - 2, MyFigure2.points.size() - 1};
			unsigned int vier[] = {MyFigure2.points.size() - 3, MyFigure2.points.size() - 1, MyFigure2.points.size() - 2};

			std::vector<int> Een(een, een + 3);
			std::vector<int> Twee(twee, twee + 3);
			std::vector<int> Drie(drie, drie + 3);
			std::vector<int> Vier(vier, vier + 3);

			FaceLines.point_indexes = Een;
			MyFigure2.faces.push_back(FaceLines);
			FaceLines.point_indexes = Twee;
			MyFigure2.faces.push_back(FaceLines);
			FaceLines.point_indexes = Drie;
			MyFigure2.faces.push_back(FaceLines);
			FaceLines.point_indexes = Vier;
			MyFigure2.faces.push_back(FaceLines);
		}

		MyFigure = MyFigure2;
		MyFigure2.points.clear();
		MyFigure2.faces.clear();
	}

	for (unsigned int i = 0; i < MyFigure.points.size(); i++) {
		MyFigure.points[i].normalise();								//Normalise all points afterwards, so they all have the same distance from the center.
	}
}

void createCone(Figure &MyFigure, unsigned int n, double height) {
	for (unsigned int i = 0; i <= n; i++) {							//Create the points of a cone.
		MyFigure.points.push_back(Vector3D::point(cos((2 * i * PI) / n), sin((2 * i * PI) / n), 0));
	}
	MyFigure.points.push_back(Vector3D::point(0, 0, height));

	for (unsigned int i = 0; i < MyFigure.points.size() - 1; i++) {
		unsigned int een[] = {i, i + 1, MyFigure.points.size() - 1};//Create several faces using the created points.
		std::vector<int> Een(een, een + 3);
		Face FaceLines;
		FaceLines.point_indexes = Een;
		MyFigure.faces.push_back(FaceLines);
	}
}

void createCylinder(Figure &MyFigure, unsigned int n, double height) {
	Face top, bottom;
	for (unsigned int i = 0; i < n; i++) {							//Create the points of a cylinder.
		MyFigure.points.push_back(Vector3D::point(cos((2 * i * PI) / n), sin((2 * i * PI) / n), 0));
		MyFigure.points.push_back(Vector3D::point(cos((2 * i * PI) / n), sin((2 * i * PI) / n), height));
	}

	for (unsigned int i = 0; i < (n*2); i += 2) {
		top.point_indexes.push_back(i);
	}
	MyFigure.faces.push_back(top);

	for (unsigned int i = 1; i <= (n*2); i += 2) {
		bottom.point_indexes.push_back(i);
	}
	MyFigure.faces.push_back(bottom);

	for (unsigned int i = 0; i < (MyFigure.points.size()); i += 2) {
		unsigned int een[] = {i, i + 2, i + 3, i + 1};				//Create several faces using the created points.

		if(i == (MyFigure.points.size()) - 2) {						//If the face is the last one, connect the last points to the first ones.
			een[0] = i;
			een[1] = 0;
			een[2] = 1;
			een[3] = i + 1;
		}
		std::vector<int> Een(een, een + 4);
		Face FaceLines;
		FaceLines.point_indexes = Een;
		MyFigure.faces.push_back(FaceLines);
	}
}

void createTorus(Figure &MyFigure, unsigned int m, unsigned int n, double r, double R) {

	for (unsigned int i = 0; i < n; i++) {							//Create the points of a torus.
		double u = (2 * i * PI) / n;

		for(unsigned int j = 0; j < m; j++) {
			double v = (2 * j * PI) / m;
			double x = (R + (r * cos(v))) * cos(u);
			double y = (R + (r * cos(v))) * sin(u);
			double z = r * sin(v);
			MyFigure.points.push_back(Vector3D::point(x, y, z));
		}
	}

	//No idea how i did this, but it worked.
	unsigned int nn = 0;
	for (unsigned int i = 0; i < n - 1; i++) {						//For each polygon but the last one.
		for(unsigned int j = 0; j < m; j++) {						//For each point on the polygon.
			unsigned int een[] = {(j + nn), (j + nn) + m, (j + nn) + m + 1, (j + nn) + 1};

			if (j == m - 1) {
				een[0] = (j + nn);
				een[1] = (j + nn) + m;
				een[2] = nn + m;
				een[3] = nn;
			}

			std::vector<int> Een(een, een + 4);
			Face FaceLines;
			FaceLines.point_indexes = Een;
			MyFigure.faces.push_back(FaceLines);
		}
		nn += m;
	}

	for(unsigned int i = MyFigure.points.size() - m; i < MyFigure.points.size(); i++) {
		unsigned int een[] = {i, i % m, i % m + 1, i + 1};

		if (i == MyFigure.points.size() - 1) {
			een[0] = i;
			een[1] = m - 1;
			een[2] = 0;
			een[3] = MyFigure.points.size() - m;
		}

		std::vector<int> Een(een, een + 4);
		Face FaceLines;
		FaceLines.point_indexes = Een;
		MyFigure.faces.push_back(FaceLines);
	}
}

void create3DLSystem(Figure &MyFigure, string input) {
	const char* inputfile = input.c_str();
	LParser::LSystem3D l_system;								//Initialize the l_system.
	ifstream input_stream(inputfile);
	input_stream >> l_system;
	input_stream.close();

	std::set<char> Alphabet = l_system.get_alphabet();
	std::string initiator = l_system.get_initiator();
	unsigned int NrIterations = l_system.get_nr_iterations();
	std::string vervanging = "";								//A new string to help with replacement

	double angle = l_system.get_angle();
	angle = angle * (PI / 180);									//Convert to radians.

	for (unsigned int i = 0; i < NrIterations; i++) {			//Execute the replacements on the initiator.
		for (std::string::const_iterator it = initiator.begin(); it != initiator.end(); it++) {
			if (*it == '+') {
				vervanging.append("+");
			} else if (*it == '-') {
				vervanging.append("-");
			} else if (*it == '(') {
				vervanging.append("(");
			} else if (*it == ')') {
				vervanging.append(")");
			} else if (*it == '^') {
				vervanging.append("^");
			} else if (*it == '&') {
				vervanging.append("&");
			} else if (*it == '\\') {
				vervanging.append("\\");
			} else if (*it == '/') { 
				vervanging.append("/");
			} else if (*it == '|') {
				vervanging.append("|");
			} else if (*it == ' ') {
				continue;
			} else {
				vervanging.append(l_system.get_replacement(*it));
			}
		}
		initiator = vervanging;
		vervanging = "";
	}

	Vector3D H = Vector3D::vector(1, 0, 0);
	Vector3D L = Vector3D::vector(0, 1, 0);
	Vector3D U = Vector3D::vector(0, 0, 1);
	Vector3D newH, newL, newU;
	Vector3D pos = Vector3D::point(0, 0, 0);
	stack<Vector3D> stack;
	for (std::string::const_iterator itt = initiator.begin(); itt != initiator.end(); itt++) {
		if (*itt == '+') {										//Do something for each symbol in the string.
			newH = (H * cos(angle)) + (L * sin(angle));
			newL = ((-H) * sin(angle)) + (L * cos(angle));
			H = newH;
			L = newL;
		} else if (*itt == '-') {
			newH = (H * cos(-angle)) + (L * sin(-angle));
			newL = ((-H) * sin(-angle)) + (L * cos(-angle));
			H = newH;
			L = newL;
		} else if (*itt == '^') {
			newH = (H * cos(angle)) + (U * sin(angle));
			newU = ((-H) * sin(angle)) + (U * cos(angle));
			H = newH;
			U = newU;
		} else if (*itt == '&') {
			newH = (H * cos(-angle)) + (U * sin(-angle));
			newU = ((-H) * sin(-angle)) + (U * cos(-angle));
			H = newH;
			U = newU;
		} else if (*itt == '\\') {
			newL = (L * cos(angle)) - (U * sin(angle));
			newU = (L * sin(angle)) + (U * cos(angle));
			L = newL;
			U = newU;
		} else if (*itt == '/') {
			newL = (L * cos(-angle)) - (U * sin(-angle));
			newU = (L * sin(-angle)) + (U * cos(-angle));
			L = newL;
			U = newU;
		} else if (*itt == '|') {
			H = -H;
			L = -L;
		} else if (*itt == '(') {
			stack.push(pos);
			stack.push(H);
			stack.push(L);
			stack.push(U);
		} else if (*itt == ')') {
			U = stack.top();
			stack.pop();
			L = stack.top();
			stack.pop();
			H = stack.top();
			stack.pop();
			pos = stack.top();
			stack.pop();
		} else if (l_system.draw(*itt) == 1) {					//If a line has to be drawn.
			MyFigure.points.push_back(pos);
			pos += H;
			MyFigure.points.push_back(pos);

			unsigned int een[] = {MyFigure.points.size() - 2, MyFigure.points.size() - 1};
			vector<int> Een(een, een + 2);
			Face Line;
			Line.point_indexes = Een;
			MyFigure.faces.push_back(Line);
		} else {												//If no line has to be drawn.
			pos += H;
		}
	}
}
