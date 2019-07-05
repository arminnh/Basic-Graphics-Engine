#ifndef HEADER_MATRICES
#define HEADER_MATRICES

#include "tools/vector.hh"

#include "util.h"

Point2D project_point(Vector3D point, double d);

inline Vector3D cartesian_to_polar(const Vector3D p);

Matrix get_eye_point_transformation_matrix(Vector3D eye);

Matrix scale(Matrix m, double s);

Matrix rotate_x(Matrix m, double angle);
Matrix rotate_y(Matrix m, double angle);
Matrix rotate_z(Matrix m, double angle);
Matrix rotate(Matrix m, double x = 0.0, double y = 0.0, double z = 0.0);

Matrix translate_x(Matrix m, double d);
Matrix translate_y(Matrix m, double d);
Matrix translate_z(Matrix m, double d);
Matrix translate(Matrix m, double x = 0.0, double y = 0.0, double z = 0.0);

#endif