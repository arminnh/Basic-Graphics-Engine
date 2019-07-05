#include "matrices.h"

Point2D project_eye_coord_point(Vector3D point, double d)
{
    return Point2D(
        d * point.x / -point.z,
        d * point.y / -point.z
    );
}

