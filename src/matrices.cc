#include "matrices.h"
#include <cmath>

using namespace std;

Point2D project_point(Vector3D point, double d)
{
    return Point2D(
        d * point.x / -point.z,
        d * point.y / -point.z
    );
}

Vector3D cartesian_to_polar(const Vector3D p)
{
    double r = sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    double theta = atan2(p.y, p.x);
    double phi = acos(p.z / r);
    return Vector3D::point(r, theta, phi);
}

const Matrix get_eye_point_transformation_matrix(const Vector3D eye_point_cartesian)
{
    Vector3D eye_point_polar = cartesian_to_polar(eye_point_cartesian);
    const double r = eye_point_polar.x;
    const double theta = eye_point_polar.y;
    const double phi = eye_point_polar.z;

    Matrix m = Matrix();

    m(1, 1) = -sin(theta);
    m(1, 2) = -cos(theta) * cos(phi);
    m(1, 3) = cos(theta) * sin(phi);

    m(2, 1) = cos(theta);
    m(2, 2) = -sin(theta) * cos(phi);
    m(2, 3) = sin(theta) * sin(phi);

    m(3, 2) = sin(phi);
    m(3, 3) = cos(phi);

    m(4, 3) = -r;

    return m;
}