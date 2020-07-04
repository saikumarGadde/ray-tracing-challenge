#include "core/models/vector.h"

Eigen::Vector3f Color(float r, float g, float b) {
  Eigen::Vector3f color;
  color(0) = r;
  color(1) = g;
  color(2) = b;
}

Eigen::Vector4f Point1Dim(float x, float y, float z) {
  Eigen::Vector4f point;
  point << x, y, z, 1.0f;
  return point;
}

Eigen::Matrix<float, 4, 1> Point2Dim(float x, float y, float z) {
  Eigen::Matrix<float, 4, 1> point;
  point << x, y, z, 1.0f;
  return point;
}

Eigen::Vector4f Vector1Dim(float x, float y, float z) {
  Eigen::Vector4f vector;
  vector << x, y, z, 0.0f;
  return vector;
}

Eigen::Matrix<float, 4, 1> Vector2Dim(float x, float y, float z) {
  Eigen::Matrix<float, 4, 1> vector;
  vector << x, y, z, 0.0f;
  return vector;
}
