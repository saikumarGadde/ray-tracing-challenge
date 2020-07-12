#include "core/models/plane.h"

Eigen::Vector4f Plane::NormalAt(Eigen::Vector4f point) {
  return Vector1Dim(0, 1, 0);
}