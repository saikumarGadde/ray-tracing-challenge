#include "core/models/object_abstract.h"
#include <iostream>
#include "core/ops/vector_ops.h"

void ObjectAbstract::SetTransform(Eigen::Matrix4f transform) {
  // Sets the transform
  transform_ = transform;
}

void ObjectAbstract::SetMaterial(struct Material material) {
  // Sets the material
  material_ = material;
}

Eigen::Matrix4f& ObjectAbstract::GetTransform() {
  // Returns transform
  return transform_;
}

struct Material& ObjectAbstract::GetMaterial() {
  // Returns Material of the sphere
  return material_;
}

Eigen::Vector4f ObjectAbstract::NormalAtWorldPoint(
    Eigen::Vector4f world_point) {
  // Obtain the normal in the object space
  Eigen::Vector4f object_point = (transform_.inverse()) * world_point;
  Eigen::Vector4f object_normal = NormalAt(object_point);

  // Transforms the normal in the object space to the world space
  Eigen::Vector4f world_normal =
      (transform_.inverse()).transpose() * object_normal;
  world_normal[3] = 0;
  world_normal = Normalization(world_normal);
  // Return the normalized normal of the sphere
  return world_normal;
}

object_type::ObjectType ObjectAbstract::GetObjectType() { return object_type_; }