#ifndef HEADER_MATRICES
#define HEADER_MATRICES

#include "../tools/vector.hh"

#include "util.h"

Point2D project_point(Vector3D point, double d);

inline Vector3D cartesian_to_polar(const Vector3D p);

const Matrix get_eye_point_transformation_matrix(const Vector3D eye_point_cartesian);

const Matrix get_scaling_matrix(const double s);

const Matrix get_rotation_x_matrix(const double angle);
const Matrix get_rotation_y_matrix(const double angle);
const Matrix get_rotation_z_matrix(const double angle);
const Matrix get_rotation_matrix(const double x, const double y, const double z);

const Matrix get_translation_x_matrix(const double d);
const Matrix get_translation_y_matrix(const double d);
const Matrix get_translation_z_matrix(const double d);
const Matrix get_translation_matrix(const double x, const double y, const double z);

const Matrix get_all_transformations_matrix(const Vector3D eye_point, const Vector3D center, const double rotate_x_degrees, const double rotate_y_degrees, const double rotate_z_degrees, const double scale);

#endif