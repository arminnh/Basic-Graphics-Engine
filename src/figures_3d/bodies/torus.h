#ifndef HEADER_TORUS
#define HEADER_TORUS

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util.h"
#include "../figure.h"

class Torus : public Figure
{
public:
    Torus(ini::Section &config)
        : Figure(config)
    {
        const double r_midpoint = config["R"].as_double_or_die();
        const double r_band = config["r"].as_double_or_die();
        const int n = config["n"].as_int_or_die();
        const int m = config["m"].as_int_or_die();

        // the i is for the points along the band ((x, y) position)
        // the j is for the points on the circles of the band (z position)
        for (int i = 0; i < n; i++) {
            // horizontal angle (xy plane)
            double u = (double) i / n * 2.0 * M_PI;

            for (int j = 0; j < m; j++) {
                // vertical angle (z plane)
                double v = (double) j / m * 2.0 * M_PI;

                this->points.push_back(Vector3D::point(
                    (r_midpoint + r_band * cos(v)) * cos(u),
                    (r_midpoint + r_band * cos(v)) * sin(u),
                    r_band * sin(v)
                ));
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // torus is made up by rectangles, in this case the order is
                // bottom left, bottom right (+ m), top right (+ m + 1), top left (+ 1)
                // modulos are used to wrap around the band as well as each circle nicely
                this->faces.push_back(Face(std::vector<int>{
                    (i * m) + j,
                    ((i * m) + m) % (m * n) + j,
                    ((i * m) + m) % (m * n) + (j + 1) % m,
                    (i * m) + (j + 1) % m
                }));
            }
        }
    }
};

#endif