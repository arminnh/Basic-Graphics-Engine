#ifndef HEADER_TETRAHEDRON
#define HEADER_TETRAHEDRON

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Tetrahedron : public Figure
{
public:
    Tetrahedron(ini::Section &config)
        : Figure(config)
    {
        this->points.push_back(Vector3D::point(1, -1, -1));
        this->points.push_back(Vector3D::point(-1, 1, -1));
        this->points.push_back(Vector3D::point(1, 1, 1));
        this->points.push_back(Vector3D::point(-1, -1, 1));

        this->faces.push_back(Face(std::vector<int>{0, 1, 2}));
        this->faces.push_back(Face(std::vector<int>{0, 1, 3}));
        this->faces.push_back(Face(std::vector<int>{0, 2, 3}));
        this->faces.push_back(Face(std::vector<int>{1, 2, 3}));
    }
};

#endif