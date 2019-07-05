#include <sstream>

#include "figures.h"
#include "tools/ini_configuration.hh"

Figure::Figure(ini::Section &config)
{
    ini::DoubleTuple center = config["center"].as_double_tuple_or_die();
    ini::DoubleTuple color = config["color"].as_double_tuple_or_die();

    this->center = tuple_to_vector(center);
    this->color = tuple_to_color(color);
}

Lines2D Figure::project()
{
    Lines2D lines;

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

    for (auto p : this->points) {
        s << p << std::endl;
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