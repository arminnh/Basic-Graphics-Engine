#ifndef HEADER_UTIL
#define HEADER_UTIL

#include <cmath>
#include <iostream>
#include <list>
#include <limits>
#include "../tools/EasyImage.h"
#include "../tools/ini_configuration.hh"
#include "../tools/vector.hh"

#define VERBOSE false
#define M_PHI 1.6180339887
#define M_GOLDEN_RATIO M_PHI
#define INF std::numeric_limits<double>::infinity();

class Point2D {
   public:
    double x, y;

    Point2D(double x, double y) : x(x), y(y){};

    friend std::ostream &operator<<(std::ostream &out, const Point2D &p);
};

class Line2D {
   public:
    Point2D p1, p2;
    double z1, z2; // original z coordinates before projection for z buffering
    img::Color c = img::Color(255, 255, 255);

    Line2D(Point2D p1, Point2D p2) : p1(p1), p2(p2){};

    Line2D(Point2D p1, Point2D p2, img::Color c) : p1(p1), p2(p2), c(c){};

    Line2D(Point2D p1, Point2D p2, double z1, double z2, img::Color c) : p1(p1), p2(p2), z1(z1), z2(z2), c(c){};

    Line2D(double x1, double y1, double x2, double y2) : p1(Point2D(x1, y1)), p2(Point2D(x2, y2)){};

    Line2D(double x1, double y1, double x2, double y2, img::Color c) : p1(Point2D(x1, y1)), p2(Point2D(x2, y2)), c(c){};

    friend std::ostream &operator<<(std::ostream &out, const Line2D &l);
};

typedef std::list<Line2D> Lines2D;

inline Point2D project_point(Vector3D point, double d) {
    return Point2D(
        d * point.x / -point.z,
        d * point.y / -point.z);
}

inline int round_to_int(double d) {
    return d < 0 ? std::ceil(d - 0.5) : std::floor(d + 0.5);
}

inline double deg_to_rad(double degrees) {
    return degrees * M_PI / 180.0;
}

inline double rad_to_deg(double radians) {
    return radians * 180.0 / M_PI;
}

inline img::Color tuple_to_color(ini::DoubleTuple tuple) {
    return img::Color(
        round_to_int(255.0 * tuple[0]),
        round_to_int(255.0 * tuple[1]),
        round_to_int(255.0 * tuple[2]));
}

inline Vector3D tuple_to_vector(ini::DoubleTuple tuple) {
    return Vector3D::point(tuple[0], tuple[1], tuple[2]);
}

inline Vector3D cartesian_to_polar(const Vector3D p) {
    double r = sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    double theta = atan2(p.y, p.x);
    double phi = acos(p.z / r);
    return Vector3D::point(r, theta, phi);
}

img::EasyImage draw_2d_lines(const Lines2D &lines, const int size, const img::Color);

#endif