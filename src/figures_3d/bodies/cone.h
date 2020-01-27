#ifndef HEADER_CONE
#define HEADER_CONE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"
#include "../../tools/vector.hh"

#include "../../util/util.h"
#include "../figure.h"

class Cone : public Figure
{
public:
    Cone(ini::Section &config)
        : Figure(config)
    {
        const int n = config["n"].as_int_or_die();
        const double height = config["height"].as_double_or_die();

        // add points on the base of the cone
        for (int i = 0; i < n + 1; i++) {
            this->points.push_back(this->get_point_i_on_base(i, n));
        }

        // add top point of the cone
        this->points.push_back(Vector3D::point(0, 0, height));

        for (int i = 1; i < (int) this->points.size(); i++) {
            this->faces.push_back(Face(std::vector<int>{i, n + 1, i - 1}));
        }
    }

private:
    Vector3D get_point_i_on_base(const int i, const int n)
    {
        return Vector3D::point(
            std::cos(2 * i * M_PI / n),
            std::sin(2 * i * M_PI / n),
            0
        );
    }
};

#endif