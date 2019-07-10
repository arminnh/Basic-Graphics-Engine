#ifndef HEADER_OCTAHEDRON
#define HEADER_OCTAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Octahedron : public Figure
{
public:
    Octahedron(ini::Section &config)
        : Figure(config)
    {
        this->points.push_back(Vector3D::point(0, 0, -1)); // bottom point
        this->points.push_back(Vector3D::point(1, 0, 0));
        this->points.push_back(Vector3D::point(0, -1, 0));
        this->points.push_back(Vector3D::point(-1, 0, 0));
        this->points.push_back(Vector3D::point(0, 1, 0));
        this->points.push_back(Vector3D::point(0, 0, 1)); // top point

        // bottom half
        this->faces.push_back(Face(std::vector<int>{3, 0, 2}));
        this->faces.push_back(Face(std::vector<int>{4, 0, 3}));
        this->faces.push_back(Face(std::vector<int>{2, 0, 1}));
        this->faces.push_back(Face(std::vector<int>{1, 0, 4}));

        // top half
        this->faces.push_back(Face(std::vector<int>{3, 5, 2}));
        this->faces.push_back(Face(std::vector<int>{4, 5, 3}));
        this->faces.push_back(Face(std::vector<int>{2, 5, 1}));
        this->faces.push_back(Face(std::vector<int>{1, 5, 4}));
    }
};

#endif