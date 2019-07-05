#ifndef HEADER_FIGURES
#define HEADER_FIGURES

#include <list>
#include <vector>

#include "tools/vector.hh"
#include "tools/EasyImage.h"
#include "util.h"

class Face
{
public:
    std::vector<int> point_indexes;

    const std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &o, const Face &f);
};

class Figure
{
public:
    Figure(ini::Section &config);

    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Vector3D center = Vector3D::point(0, 0, 0);

    double scale = 1;
    double rotation_x = 0;
    double rotation_y = 0;
    double rotation_z = 0;

    img::Color color;

    Lines2D project();

    virtual const std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &o, const Figure &f);
};

typedef std::list<Figure> Figures;

#endif