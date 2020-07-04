#pragma once
#define _USE_MATH_DEFINES
#include "core/models/material.h"
#include "core/ops/vector_ops.h"

// Sphere class
class Sphere {
 public:
  // Constructor of the Sphere with a center, radius, transform and material
  Sphere(Eigen::Vector4f center, float radius, Eigen::Matrix4f transform,
         struct Material material)
      : center_(center),
        radius_(radius),
        transform_(transform),
        material_(material) {}

  Sphere() {
    center_ << 0.0f, 0.0f, 0.0f, 1.0f;
    radius_ = 1;
    transform_ = Eigen::Matrix4f::Identity();
  }

  // Sets transform matrix of the sphere
  void SetTransform(Eigen::Matrix4f transform_matrix);

  // Sets Material object of the sphere
  void SetMaterial(struct Material material);

  // Gets Material of the Sphere
  struct Material& GetMaterial();

  // Gets Transform of the sphere
  Eigen::Matrix4f GetTransform();

  // Gets Center of the sphere
  Eigen::Vector4f GetCenter();

  // Gets radius of the sphere
  float GetRadius();

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
