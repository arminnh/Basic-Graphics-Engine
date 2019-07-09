#include <sstream>

#include "line_drawings.h"

LineDrawing::LineDrawing(ini::Section &config) : Figure(config)
{
    const int nr_points = config["nrPoints"].as_int_or_die();
    const int nr_lines = config["nrLines"].as_int_or_die();

    for (int point_nr = 0; point_nr < nr_points; point_nr++) {
        ini::DoubleTuple point = config["point" + std::to_string(point_nr)].as_double_tuple_or_die();
        this->points.push_back(tuple_to_vector(point));
    }

    for (int line_nr = 0; line_nr < nr_lines; line_nr++) {
        ini::IntTuple line = config["line" + std::to_string(line_nr)].as_int_tuple_or_die();
        this->lines.push_back(std::make_tuple(line[0], line[1]));
    }
}

Lines2D LineDrawing::project(const Vector3D &eye_point, double d) const
{
    Lines2D lines;

    std::map<int, Point2D> projected_points = this->project_points(d);

    int p1_i, p2_i;
    for (std::tuple<int, int> point_indexes : this->lines) {
        std::tie(p1_i, p2_i) = point_indexes;

        lines.push_back(Line2D(projected_points.at(p1_i), projected_points.at(p2_i), this->color));
    }

    return lines;
}

const std::string LineDrawing::to_string() const
{
    std::ostringstream s;
    s << "LineDrawing{ " << ((Figure) *this);

    s << ",\nlines: [" << std::endl;

    int i = 0;
    for (auto l: this->lines) {
        s << "Line " << i << ": (" << std::get<0>(l) << " -> " << std::get<1>(l) << "), ";
        i++;
    }

    s << "]}";
    return s.str();
}

std::ostream &operator<<(std::ostream &o, const LineDrawing &ld)
{
    o << ld.to_string();
    return o;
}
