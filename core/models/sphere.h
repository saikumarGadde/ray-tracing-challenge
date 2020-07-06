#pragma once
#define _USE_MATH_DEFINES
#include "core/models/material.h"
#include "core/models/object_type.h"
#include "core/ops/vector_ops.h"

// Sphere class
class Sphere {
 public:
  Sphere(object_type::ObjectType object_type) {
    if (object_type == object_type::ObjectType::SPHERE) {
      // Initialize a new sphere
      center_ << 0.0f, 0.0f, 0.0f, 1.0f;
      radius_ = 1;
      transform_ = Eigen::Matrix4f::Identity();
    }
  }

  // Setters
  void SetCenter(Eigen::Vector4f center);
  void SetRadius(float radius);
  void SetTransform(Eigen::Matrix4f transform_matrix);
  void SetMaterial(struct Material material);
  // Getters
  Eigen::Vector4f GetCenter();
  float GetRadius();
  Eigen::Matrix4f& GetTransform();
  struct Material& GetMaterial();

  // Calculate Normat at a given point on a sphere
  Eigen::Vector4f NormalAt(Eigen::Vector4f point);

  // Normal At World point
  Eigen::Vector4f NormalAtWorldPoint(Eigen::Vector4f world_point);

 private:
  // Store the center fo the sphere
  Eigen::Vector4f center_;
  // Store the radius of the Sphere
  float radius_;
  // transform of the sphere object
  Eigen::Matrix4f transform_;
  // Material of the object
  struct Material material_;
};
