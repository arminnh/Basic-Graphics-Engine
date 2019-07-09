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

const Matrix get_scaling_matrix(const double s)
{
    Matrix m = Matrix();
    m(1, 1) = s;
    m(2, 2) = s;
    m(3, 3) = s;
    return m;
}

const Matrix get_rotation_x_matrix(const double angle_rad)
{
    Matrix m = Matrix();
    m(2, 2) = cos(angle_rad);
    m(2, 3) = sin(angle_rad);
    m(3, 2) = -sin(angle_rad);
    m(3, 3) = cos(angle_rad);
    return m;
}

const Matrix get_rotation_y_matrix(const double angle_rad)
{
    Matrix m = Matrix();
    m(1, 1) = cos(angle_rad);
    m(1, 3) = -sin(angle_rad);
    m(3, 1) = sin(angle_rad);
    m(3, 3) = cos(angle_rad);
    return m;
}

const Matrix get_rotation_z_matrix(const double angle_rad)
{
    Matrix m = Matrix();
    m(1, 1) = cos(angle_rad);
    m(1, 2) = sin(angle_rad);
    m(2, 1) = -sin(angle_rad);
    m(2, 2) = cos(angle_rad);
    m(3, 3) = 1;
    return m;
}

const Matrix get_rotation_matrix(const double x_rad, const double y_rad, const double z_rad)
{
    return get_rotation_x_matrix(x_rad) * get_rotation_y_matrix(y_rad) * get_rotation_z_matrix(z_rad);
}

const Matrix get_translation_matrix(Vector3D v)
{
    Matrix m = Matrix();
    m(4, 1) = v.x;
    m(4, 2) = v.y;
    m(4, 3) = v.z;
    return m;
}


const Matrix get_all_transformations_matrix(const Vector3D eye_point, const Vector3D center, const double rotate_x_degrees, const double rotate_y_degrees, const double rotate_z_degrees, const double scale)
{
    Matrix m = get_translation_matrix(center);
    m = m * get_rotation_matrix(
        deg_to_rad(rotate_x_degrees),
        deg_to_rad(rotate_y_degrees),
        deg_to_rad(rotate_z_degrees)
    );
    m = m * get_scaling_matrix(scale);
    m = m *  get_eye_point_transformation_matrix(eye_point);
    return m;
}