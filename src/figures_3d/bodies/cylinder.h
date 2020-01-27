#ifndef HEADER_CYLINDER
#define HEADER_CYLINDER

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util/util.h"
#include "../figure.h"

class Cylinder : public Figure
{
public:
    Cylinder(ini::Section &config)
        : Figure(config)
    {
        const int n = config["n"].as_int_or_die();
        const double height = config["height"].as_double_or_die();

        // add points on bottom
        for (int i = 0; i < n; i++) {
            this->points.push_back(this->get_point_i_on_base(i, n, 0));
        }

        // add points on top
        for (int i = 0; i < n; i++) {
            this->points.push_back(this->get_point_i_on_base(i, n, height));
        }

        for (int i = 1; i < n; i++) {
            this->faces.push_back(Face(std::vector<int>{i, i + n, i + n - 1, i - 1}));
        }

        // connect end to begin
        this->faces.push_back(Face(std::vector<int>{0, n, 2 * n - 1, n - 1}));
    }

private:
    Vector3D get_point_i_on_base(const int i, const int n, const double height)
    {
        return Vector3D::point(
            std::cos(2 * i * M_PI / n),
            std::sin(2 * i * M_PI / n),
            height
        );
    }
};

#endif