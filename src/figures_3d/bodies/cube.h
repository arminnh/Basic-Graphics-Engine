#ifndef HEADER_CUBE
#define HEADER_CUBE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Cube : public Figure
{
public:
    Cube(ini::Section &config)
        : Figure(config)
    {
        this->points.push_back(Vector3D::point(1, -1, -1));
        this->points.push_back(Vector3D::point(1, -1, 1));
        this->points.push_back(Vector3D::point(-1, -1, 1));
        this->points.push_back(Vector3D::point(-1, -1, -1));
        this->points.push_back(Vector3D::point(1, 1, -1));
        this->points.push_back(Vector3D::point(1, 1, 1));
        this->points.push_back(Vector3D::point(-1, 1, 1));
        this->points.push_back(Vector3D::point(-1, 1, -1));

        this->faces.push_back(Face(std::vector<int>{4, 5, 6, 7})); // back
        this->faces.push_back(Face(std::vector<int>{3, 2, 6, 7})); // left side
        this->faces.push_back(Face(std::vector<int>{0, 4, 7, 3})); // bottom
        this->faces.push_back(Face(std::vector<int>{0, 1, 2, 3})); // front
        this->faces.push_back(Face(std::vector<int>{0, 4, 5, 1})); // right side
        this->faces.push_back(Face(std::vector<int>{1, 5, 6, 2})); // top
    }
};

#endif