#include "core/models/sphere.h"

Eigen::Vector4f Sphere::NormalAt(Eigen::Vector4f point) {
  //
  Eigen::Vector4f normal_vector = point - GetCenter();
  normal_vector = Normalization(normal_vector);
  return normal_vector;
}

Eigen::Vector4f Sphere::NormalAtWorldPoint(Eigen::Vector4f world_point) {
  // Obtain the normal in the object space
  Eigen::Vector4f object_point = (transform_.inverse()) * world_point;
  Eigen::Vector4f object_normal = object_point - center_;

  // Transforms the normal in the object space to the world space
  Eigen::Vector4f world_normal =
      (transform_.inverse()).transpose() * object_normal;
  world_normal[3] = 0;
  world_normal = Normalization(world_normal);
  // Return the normalized normal of the sphere
  return world_normal;
}

void Sphere::SetTransform(Eigen::Matrix4f transform) {
  // Set transform to the sphere object
  transform_ = transform;
}

void Sphere::SetMaterial(struct Material material) {
  // Set material to the sphere object
  material_ = material;
}

struct Material& Sphere::GetMaterial() {
  return material_;
}

Eigen::Matrix4f Sphere::GetTransform() {
  // Return transform of the sphere
  return transform_;
}

Eigen::Vector4f Sphere::GetCenter() {
  //
  return center_;
}

float Sphere::GetRadius() {
  // Returns radius of the sphere
  return radius_;
};