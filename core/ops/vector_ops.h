#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

// Magnitude of an vector
float Magnitude(Eigen::Vector4f vector);

// Normalization of the point
Eigen::Vector4f Normalization(Eigen::Vector4f vector);

// Cross product of two Eigen vectors
Eigen::Vector4f CrossProduct4f(Eigen::Vector4f vector1,
                               Eigen::Vector4f vector2);

// Negating a vector
Eigen::Vector4f Negate(Eigen::Vector4f vector);
Eigen::Vector4f NegateVector(Eigen::Vector4f vector);
Eigen::Vector4f NegatePoint(Eigen::Vector4f point);

// Scalar multiplication of a vector, Vector Scalar Multiply
Eigen::Vector4f VectorScalarMultiply(Eigen::Vector4f vector,
                                     float scalar_value);

// Scalar division of a vector, VectorScalarDivide
Eigen::Vector4f VectorScalarDivide(Eigen::Vector4f vector, float scalar_value);