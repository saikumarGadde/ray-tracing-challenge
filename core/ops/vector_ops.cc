#include "core/ops/vector_ops.h"
#include <cassert>

float Magnitude(Eigen::Vector4f vector) { return vector.norm(); }

Eigen::Vector4f Normalization(Eigen::Vector4f vector) {
  assert(vector[3] == 0.0f);
  Eigen::Vector4f normalized_vector;
  float magnitude = vector.norm();
  return vector / magnitude;
}

// Cross product of Eigen::Vector4f 's
Eigen::Vector4f CrossProduct4f(Eigen::Vector4f vector1,
                               Eigen::Vector4f vector2) {
  assert((vector1[3] == 0.0f) && (vector2[3] == 0.0f));
  Eigen::Vector3f cross_product;
  Eigen::Vector3f c1(vector1[0], vector1[1], vector1[2]);
  Eigen::Vector3f c2(vector2[0], vector2[1], vector2[2]);
  cross_product = c1.cross(c2);
  Eigen::Vector4f result(cross_product[0], cross_product[1], cross_product[2],
                         0.0f);
  return result;
}

Eigen::Vector4f Negate(Eigen::Vector4f vector) {
  Eigen::Vector4f opposite;
  opposite(0) = -vector(0);
  opposite(1) = -vector(1);
  opposite(2) = -vector(2);
  opposite(3) = vector(3);
  return opposite;
}

Eigen::Vector4f NegateVector(Eigen::Vector4f vector) {
  assert(vector[3] == 0.0f);
  return -vector;
}

Eigen::Vector4f NegatePoint(Eigen::Vector4f point) {
  assert(point[3] == 1.0f);
  point = -point;
  point(3) = -point(3);
  return point;
}

// Scalar multiplication of a vector
Eigen::Vector4f VectorScalarMultiply(Eigen::Vector4f vector,
                                     float scalar_value) {
  return vector * scalar_value;
}

Eigen::Vector4f VectorScalarDivide(Eigen::Vector4f vector, float scalar_value) {
  return vector / scalar_value;
}
