#include "core/models/object.h"

// Getters
struct Material& Object::GetMaterial() {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->GetMaterial();
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->GetMaterial();
  }
}
Eigen::Matrix4f Object::GetTransform() {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->GetTransform();
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->GetTransform();
  } else {
    //
  }
}

// Setters
void Object::SetTransform(Eigen::Matrix4f transform) {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->SetTransform(transform);
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->SetTransform(transform);
  }
}
void Object::SetMaterial(struct Material material) {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->SetMaterial(material);
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->SetMaterial(material);
  }
}

Eigen::Vector4f Object::NormalAtLocalPoint(Eigen::Vector4f point) {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->NormalAt(point);
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->NormalAt(point);
  }
}

Eigen::Vector4f Object::NormalAtWorldPoint(Eigen::Vector4f world_point) {
  if (object_type_ == object_type::ObjectType::SPHERE) {
    return sphere_->NormalAtWorldPoint(world_point);
  } else if (object_type_ == object_type::ObjectType::PLANE) {
    return plane_->NormalAtWorldPoint(world_point);
  }
}