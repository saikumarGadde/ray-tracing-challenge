#pragma once
#define _USE_MATH_DEFINES
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

// Creation of point and vector in Eigen library for efficient computation
Eigen::Vector4f Point1Dim(float x, float y, float z);
Eigen::Matrix<float, 4, 1> Point2Dim(float x, float y, float z);

Eigen::Vector4f Vector1Dim(float x, float y, float z);
Eigen::Matrix<float, 4, 1> Vector2Dim(float x, float y, float z);

// Transformations required

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
