#include "core/chapter6/chapter6.h"
#include "core/chapter5/chapter5.h"

Eigen::Vector4f NormalAt(struct Sphere sphere, Eigen::Vector4f& point) {
  // @TODO

  Eigen::Vector4f normal_vector = point - sphere.center;
  normal_vector = Normalization(normal_vector);
  return normal_vector;
}