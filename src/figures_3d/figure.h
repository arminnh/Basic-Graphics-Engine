#ifndef HEADER_FIGURES
#define HEADER_FIGURES

#include <list>
#include <vector>

#include "../tools/EasyImage.h"
#include "../tools/vector.hh"

#include "../util/util.h"

class Face {
   public:
    std::vector<int> point_indexes;

    Face(std::vector<int> index_list) : point_indexes(index_list) {}

    const std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &o, const Face &f);
};

class Figure {
   public:
    Figure();
    Figure(ini::Section &config);

    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Vector3D center = Vector3D::point(0, 0, 0);

    double scale = 1;
    double rotation_x = 0;
    double rotation_y = 0;
    double rotation_z = 0;

    img::Color color;

    void apply_transformation(const Matrix &m);

    virtual Lines2D project(double d) const;

    virtual const std::string to_string() const;
    friend std::ostream &operator<<(std::ostream &o, const Figure &f);

   protected:
    const std::map<int, Point2D> project_points(double d) const;
};

#endif