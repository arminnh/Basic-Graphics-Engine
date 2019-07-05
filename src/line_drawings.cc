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

const std::string LineDrawing::to_string() const
{
    std::ostringstream s;
    s << "LineDrawing{ " << ((Figure) *this);

    s << ",\nlines: [" << std::endl;

    for (auto l: this->lines) {
        s << std::get<0>(l) << " -> " << std::get<0>(l) << ", ";
    }

    s << "]}";
    return s.str();
}

std::ostream &operator<<(std::ostream &o, const LineDrawing &ld)
{
    o << ld.to_string();
    return o;
}
