#ifndef HEADER_DODECAHEDRON
#define HEADER_DODECAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Dodecahedron : public Figure
{
public:
    Dodecahedron(ini::Section &config)
        : Figure(config)
    {
        std::vector<int> points {-1, 1};
        const double phi = M_GOLDEN_RATIO;

        for (int x : points) {
            for (int y : points) {
                for (int z : points) {
                    this->points.push_back(Vector3D::point(x, y, z));

                    // golden ration points with varying y and z
                    if (x == 1) {
                        this->points.push_back(Vector3D::point(0, y * phi, z / phi));
                    }

                    // golden ration points with varying x and z
                    if (y == 1) {
                        this->points.push_back(Vector3D::point(x / phi, 0, z * phi));
                    }

                    // golden ration points with varying x and y
                    if (z == 1) {
                        this->points.push_back(Vector3D::point(x * phi, y / phi, 0));
                    }
                }
            }
        }

        for (int i = 0; i < this->points.size(); i++) {
            for (int j = i + 1; j < this->points.size(); j++) {
                this->faces.push_back(Face(std::vector<int>{i, j}));
                // this->faces.push_back(Face(std::vector<int>{i, (i + 1) % this->points.size()}));
            }
        }
    }
};

#endif