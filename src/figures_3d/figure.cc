#include <sstream>

#include "../tools/ini_configuration.hh"

#include "figure.h"
#include "../matrices.h"

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
    for (int i = 0; i < this->points.size(); i++) {
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

Lines2D Figure::project(const Vector3D &eye_point, double d) const
{
    Lines2D lines;

    std::vector<Vector3D> new_points;
    std::map<int, Point2D> projected_points = this->project_points(d);

    for (Face face : this->faces) {
        for (int i = 1; i < face.point_indexes.size(); i++) {
            lines.push_back(Line2D(
                projected_points.at(face.point_indexes.at(i - 1)),
                projected_points.at(face.point_indexes.at(i)),
                this->color
            ));
        }

        // add the line from the last point in the face to the first point in the face
        if (face.point_indexes.size() > 2) {
            lines.push_back(Line2D(
                projected_points.at(face.point_indexes.at(0)),
                projected_points.at(face.point_indexes.at(face.point_indexes.size() - 1)),
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