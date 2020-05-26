#include "core/chapter5/chapter5.h"

Eigen::Vector4f Position(struct Ray ray, float distance) {
  return ray.origin + (ray.direction * distance);
}

// Mehtod to intersect the ray and sphere
void Intersect(struct Ray ray, struct Sphere sphere) {
  //
}