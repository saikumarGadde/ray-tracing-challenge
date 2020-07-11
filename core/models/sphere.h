#pragma once
#define _USE_MATH_DEFINES
#include "core/models/material.h"
#include "core/models/object_abstract.h"
#include "core/models/object_type.h"
#include "core/models/vector.h"
#include "core/ops/vector_ops.h"

// Sphere class
class Sphere : public ObjectAbstract {
 public:
  Sphere(object_type::ObjectType object_type) : ObjectAbstract(object_type) {}

  virtual ~Sphere() {}

  // Setters
  void SetCenter(Eigen::Vector4f center);
  void SetRadius(float radius);

  // Getters
  Eigen::Vector4f GetCenter();
  float GetRadius();

  // Calculate Normat at a given point on a sphere
  Eigen::Vector4f NormalAt(Eigen::Vector4f point);

  // Override sphere initialization
  void InitSphere();

 private:
  // Store the center fo the sphere
  Eigen::Vector4f center_;
  // Store the radius of the Sphere
  float radius_;
};
