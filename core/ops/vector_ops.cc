#include "core/ops/vector_ops"

namespace OPS {
namespace VECTOR {

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

float Magnitude(Eigen::Vector4f vector) {
  return sqrt(vector[0] * vector[0] + vector[1] * vector[1] +
              vector[2] * vector[2]);
}

Eigen::Vector4f Normalization(Eigen::Vector4f vector) {
  Eigen::Vector4f normalized_vector;
  float magnitude = Magnitude(vector);
  normalized_vector[0] = vector[0] / magnitude;
  normalized_vector[1] = vector[1] / magnitude;
  normalized_vector[2] = vector[2] / magnitude;
  normalized_vector[3] = vector[3];
  return normalized_vector;
}

}  // namespace VECTOR
}  // namespace OPS