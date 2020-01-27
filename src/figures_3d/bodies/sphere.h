#ifndef HEADER_SPHERE
#define HEADER_SPHERE

#include <tuple>
#include <vector>

#include "../../tools/EasyImage.h"
#include "../../tools/ini_configuration.hh"

#include "../../util/util.h"
#include "../figure.h"

class Sphere : public Figure
{
public:
    Sphere(ini::Section &config)
        : Figure(config)
    {
        const int n = config["n"].as_int_or_die();

        Icosahedron ico(config);
        this->points = ico.points;
        this->faces = ico.faces;

        for (int i = 0; i < n; i++) {
            std::vector<Vector3D> new_points;
            std::vector<Face> new_faces;

            for (const Face &f : this->faces) {
                int p_i = new_points.size();

                Vector3D A = this->points.at(f.point_indexes.at(0));
                Vector3D B = this->points.at(f.point_indexes.at(1));
                Vector3D C = this->points.at(f.point_indexes.at(2));
                new_points.push_back(A);
                new_points.push_back(B);
                new_points.push_back(C);
                new_points.push_back((A + B) / 2); // D
                new_points.push_back((A + C) / 2); // E
                new_points.push_back((B + C) / 2); // F

                new_faces.push_back(Face(std::vector<int>{p_i, p_i + 3, p_i + 4}));     // A D E
                new_faces.push_back(Face(std::vector<int>{p_i + 3, p_i + 5, p_i + 4})); // D F E
                new_faces.push_back(Face(std::vector<int>{p_i + 3, p_i + 1, p_i + 5})); // D B F
                new_faces.push_back(Face(std::vector<int>{p_i + 5, p_i + 2, p_i + 4})); // F C E
            }

            this->points = new_points;
            this->faces = new_faces;
        }

        for (Vector3D &p : this->points) {
            p.normalise();
        }
    }
};

#endif