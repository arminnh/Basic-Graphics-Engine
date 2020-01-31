#include <sstream>

#include "../tools/ini_configuration.hh"

#include "figure.h"
#include "../util/transformation_matrices.h"

Figure::Figure(ini::Section &config)
{
    if (VERBOSE) {
        std::cout << "Figure init for type '" << config["type"].as_string_or_die() << "'" << std::endl;
    }
    ini::DoubleTuple center = config["center"].as_double_tuple_or_die();
    ini::DoubleTuple color = config["color"].as_double_tuple_or_die();

    this->center = tuple_to_vector(center);
    this->color = tuple_to_color(color);
}

void Figure::apply_transformation(const Matrix &m)
{
    for (unsigned int i = 0; i < this->points.size(); i++) {
        this->points.at(i) = this->points.at(i) * m;
    }
}

const std::map<int, Point2D> Figure::project_points(double d) const
{
    std::map<int, Point2D> projected_points;

    int i = 0;
    for (Vector3D p : this->points) {
        projected_points.insert(std::pair<int, Point2D>(i, project_point(p, d)));
        i++;
    }

    return projected_points;
}

Lines2D Figure::project(double d) const
{
    Lines2D lines;

    std::map<int, Point2D> projected_points = this->project_points(d);

    for (Face face : this->faces) {
        for (unsigned int i = 1; i < face.point_indexes.size(); i++) {
            lines.push_back(Line2D(
                projected_points.at(face.point_indexes.at(i - 1)),
                projected_points.at(face.point_indexes.at(i)),
                this->points.at(i-1).z,
                this->points.at(i).z,
                this->color
            ));
        }

        // add the line from the last point in the face to the first point in the face
        if (face.point_indexes.size() > 2) {
            int first_point_index = face.point_indexes.at(0);
            int last_point_index = face.point_indexes.at(face.point_indexes.size() - 1);

            lines.push_back(Line2D(
                projected_points.at(first_point_index),
                projected_points.at(last_point_index),
                this->points.at(first_point_index).z,
                this->points.at(last_point_index).z,
                this->color
            ));
        }
    }

    return lines;
}

const std::string Face::to_string() const
{
    std::string s = "Face { ";

    for (int i : this->point_indexes) {
        s += std::to_string(i) + ", ";
    }

    return s + "}";
}

std::ostream &operator<<(std::ostream &o, const Face &f)
{
    o << f.to_string();
    return o;
}

const std::string Figure::to_string() const
{
    std::ostringstream s;
    s << "Figure { c(" << this->center << "), points: [\n";

    int i = 0;
    for (auto p : this->points) {
        s << "Point " << i << ": " << p << std::endl;
        i++;
    }

    s << "], faces: [" << std::endl;

    for (auto f: this->faces) {
        s << f << std::endl;
    }

    s << "]}";
    return s.str();
}

std::ostream &operator<<(std::ostream &o, const Figure &f)
{
    o << f.to_string();
    return o;
}