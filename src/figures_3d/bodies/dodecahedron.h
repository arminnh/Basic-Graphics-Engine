#ifndef HEADER_DODECAHEDRON
#define HEADER_DODECAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../matrices.h"
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

        this->faces.push_back(Face(std::vector<int>{8, 15, 13, 19, 12})); // bottom
        this->faces.push_back(Face(std::vector<int>{8, 12, 10, 11, 9})); // left
        this->faces.push_back(Face(std::vector<int>{12, 19, 16, 18, 10})); // back bottom left
        this->faces.push_back(Face(std::vector<int>{13, 19, 16, 17, 14})); // back bottom right
        this->faces.push_back(Face(std::vector<int>{18, 6, 1, 11, 10})); // back top left
        this->faces.push_back(Face(std::vector<int>{17, 16, 18, 6, 5})); // back top right
        this->faces.push_back(Face(std::vector<int>{1, 2, 0, 9, 11})); // front top left
        this->faces.push_back(Face(std::vector<int>{2, 7, 5, 6, 1})); // front top right
        this->faces.push_back(Face(std::vector<int>{0, 4, 3, 7, 2})); // front center right
        this->faces.push_back(Face(std::vector<int>{8, 15, 4, 0, 9})); // front bottom left
        this->faces.push_back(Face(std::vector<int>{15, 4, 3, 14, 13})); // front bottom right
        this->faces.push_back(Face(std::vector<int>{14, 3, 7, 5, 17})); // right

        // int n_points = this->points.size();
        // for (int i = 0; i < n_points; i++) {
        //     this->points.push_back(this->points.at(i) + Vector3D::point(0.25, 0.25, 0.25));
        //     int size = this->points.size();
        //     this->faces.push_back(Face(std::vector<int>{i, size - 1}));
        // }

        // this->points.push_back(Vector3D::point(0, 0, 0));
        // this->points.push_back(Vector3D::point(3, 0, 0));
        // this->points.push_back(Vector3D::point(0, 3, 0));
        // this->points.push_back(Vector3D::point(0, 0, 3));

        // int s = this->points.size();
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 3}));
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 2}));
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 1}));

        // this->apply_transformation(get_rotation_matrix(
        //     deg_to_rad(0),
        //     deg_to_rad(0),
        //     deg_to_rad(0)
        // ));

    }
};

#endif