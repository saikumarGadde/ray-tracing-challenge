#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

namespace OPS {
namespace VECTOR {
// Creation of point and vector in Eigen library for efficient computation
Eigen::Vector4f Point1Dim(float x, float y, float z);
Eigen::Matrix<float, 4, 1> Point2Dim(float x, float y, float z);

Eigen::Vector4f Vector1Dim(float x, float y, float z);
Eigen::Matrix<float, 4, 1> Vector2Dim(float x, float y, float z);

// Magnitude of an vector
float Magnitude(Eigen::Vector4f vector);

// Normalization of the point
Eigen::Vector4f Normalization(Eigen::Vector4f vector);

}  // namespace VECTOR
}  // namespace OPS