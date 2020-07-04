#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

// Point representation in 1 Dimension (Vector)
Eigen::Vector4f Point1Dim(float x, float y, float z);

// Point representation in 2 Dimension (Represent as Matrix)
Eigen::Matrix<float, 4, 1> Point2Dim(float x, float y, float z);

// Color
Eigen::Vector3f Color(float r, float g, float b);

// Vector representation in 1 Dimension (Vector)
Eigen::Vector4f Vector1Dim(float x, float y, float z);

// Vector representation in 2 Dimension (Represent as Matrix)
Eigen::Matrix<float, 4, 1> Vector2Dim(float x, float y, float z);
