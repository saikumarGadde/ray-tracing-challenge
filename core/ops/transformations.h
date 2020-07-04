#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

// Translation transformation. A point is translated to a new point. A vector
// remains the same.
Eigen::Matrix4f Translation(float x, float y, float z);

// Scaling Transformation
// Reflection matrix is just scaling with negative values -1's
Eigen::Matrix4f Scaling(float x, float y, float z);

// Rotation along the X axis
Eigen::Matrix4f RotationX(float radians);

// Rotation along the Y Axis
Eigen::Matrix4f RotationY(float radians);

// Rotation along the Z Axis
Eigen::Matrix4f RotationZ(float radians);

// Shearing transformation
Eigen::Matrix4f Shearing(float x_y, float x_z, float y_x, float y_z, float z_x,
                         float z_y);
