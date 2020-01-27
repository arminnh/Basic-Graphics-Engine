#ifndef HEADER_ISOCAHEDRON
#define HEADER_ISOCAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util/transformation_matrices.h"
#include "../../util/util.h"
#include "../figure.h"

class Icosahedron : public Figure
{
public:
    Icosahedron(ini::Section &config)
        : Figure(config)
    {
        std::vector<int> points {-1, 1};
        const double phi = M_GOLDEN_RATIO;

        for (int i: points) {
            for (int j: points) {
                this->points.push_back(Vector3D::point(0, i, j * phi));
                this->points.push_back(Vector3D::point(j * phi, 0, i));
                this->points.push_back(Vector3D::point(i, j * phi, 0));
            }
        }

        // 5 faces for one point
        this->faces.push_back(Face(std::vector<int>{9-1, 3-1, 1-1}));
        this->faces.push_back(Face(std::vector<int>{9-1, 4-1, 3-1}));
        this->faces.push_back(Face(std::vector<int>{9-1, 11-1, 4-1}));
        this->faces.push_back(Face(std::vector<int>{9-1, 5-1, 11-1}));
        this->faces.push_back(Face(std::vector<int>{9-1, 1-1, 5-1}));

        // 5 faces for the opposite point
        this->faces.push_back(Face(std::vector<int>{6-1, 2-1, 8-1}));
        this->faces.push_back(Face(std::vector<int>{6-1, 8-1, 10-1}));
        this->faces.push_back(Face(std::vector<int>{6-1, 10-1, 12-1}));
        this->faces.push_back(Face(std::vector<int>{6-1, 12-1, 7-1}));
        this->faces.push_back(Face(std::vector<int>{6-1, 7-1, 2-1}));

        // connect the band of points in between
        this->faces.push_back(Face(std::vector<int>{4-1, 10-1, 8-1}));
        this->faces.push_back(Face(std::vector<int>{4-1, 8-1, 3-1}));
        this->faces.push_back(Face(std::vector<int>{3-1, 8-1, 2-1}));
        this->faces.push_back(Face(std::vector<int>{3-1, 2-1, 1-1}));
        this->faces.push_back(Face(std::vector<int>{1-1, 2-1, 7-1}));
        this->faces.push_back(Face(std::vector<int>{1-1, 7-1, 5-1}));
        this->faces.push_back(Face(std::vector<int>{5-1, 11-1, 12-1}));
        this->faces.push_back(Face(std::vector<int>{5-1, 12-1, 7-1}));
        this->faces.push_back(Face(std::vector<int>{10-1, 12-1, 11-1}));
        this->faces.push_back(Face(std::vector<int>{10-1, 11-1, 4-1}));

        // // rotate the figure to achieve same image as the given ones
        // this->points.push_back(Vector3D::point(0, 0, 0));
        // this->points.push_back(Vector3D::point(3, 0, 0));
        // this->points.push_back(Vector3D::point(0, 3, 0));
        // this->points.push_back(Vector3D::point(0, 0, 3));

        // int s = this->points.size();
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 3}));
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 2}));
        // this->faces.push_back(Face(std::vector<int>{s - 4, s - 1}));

        // this->apply_transformation(get_rotation_matrix(
        //     1 * M_PI / 2 / phi,
        //     0 * M_PI / 2 / phi,
        //     0 * M_PI / 2 / phi
        // ));
    }
};

#endif