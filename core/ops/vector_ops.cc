#include "core/ops/vector_ops.h"

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

// Cross product of Eigen::Vector4f 's
Eigen::Vector4f CrossProduct4f(Eigen::Vector4f vector1,
                               Eigen::Vector4f vector2) {
  Eigen::Vector4f cross_product;
  Eigen::Vector3f c1 = vector1.head(3);
  Eigen::Vector3f c2 = vector2.head(3);
  cross_product.head(3) = c1.cross(c2);
  cross_product(3) = 0.0f;
  return cross_product;
}

Eigen::Vector4f Negate(Eigen::Vector4f vector) {
  Eigen::Vector4f opposite;
  opposite(0) = -vector(0);
  opposite(1) = -vector(1);
  opposite(2) = -vector(2);
  opposite(3) = vector(3);
  return opposite;
}

// Scalar multiplication of a vector
Eigen::Vector4f VectorScalarMultiply(Eigen::Vector4f vector,
                                     float scalar_value) {
  return vector * scalar_value;
}

Eigen::Vector4f VectorScalarDivide(Eigen::Vector4f vector, float scalar_value) {
  return vector / scalar_value;
}
