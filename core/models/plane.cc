#include "core/models/plane.h"

Eigen::Vector4f Plane::NormalAt(Eigen::Vector4f point) {
  return Vector1Dim(0, 1, 0);
}

void Plane::InitPlane() {
  normal_ << 0.0f, 1.0f, 0.0f, 0.0f;
  transform_ = Eigen::Matrix4f::Identity();
  material_.rgb_color(0) = 1;
  material_.rgb_color(1) = 1;
  material_.rgb_color(2) = 1;
  material_.ambient = 0.1;
  material_.diffuse = 0.9;
  material_.specular = 0.9;
  material_.shininess = 200.0;
}

Eigen::Vector4f& Plane::GetNormal() { return normal_; }