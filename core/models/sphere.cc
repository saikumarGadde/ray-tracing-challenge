#include "core/models/sphere.h"
#include <iostream>

Eigen::Vector4f Sphere::NormalAt(Eigen::Vector4f point) {
  //
  Eigen::Vector4f normal_vector = point - GetCenter();
  normal_vector = Normalization(normal_vector);
  return normal_vector;
}

Eigen::Vector4f Sphere::GetCenter() {
  //
  return center_;
}

float Sphere::GetRadius() {
  // Returns radius of the sphere
  return radius_;
}

void Sphere::InitSphere() {
  // Initialize the sphere
  center_ = Point1Dim(0.0f, 0.0f, 0.0f);
  radius_ = 1.0f;
  transform_ = Eigen::Matrix4f::Identity();
  material_.rgb_color(0) = 1;
  material_.rgb_color(1) = 1;
  material_.rgb_color(2) = 1;
  material_.ambient = 0.1;
  material_.diffuse = 0.9;
  material_.specular = 0.9;
  material_.shininess = 200.0;
}