#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include "core/models/material.h"
#include "core/models/object_type.h"
#include "core/models/plane.h"
#include "core/models/sphere.h"
// Wrapper for all the objects

class Object {
 public:
  Object(object_type::ObjectType object_type) : object_type_(object_type) {
    if (object_type == object_type::ObjectType::SPHERE) {
      sphere_ = std::unique_ptr<Sphere>(new Sphere(object_type));
    } else if (object_type == object_type::ObjectType::PLANE) {
      plane_ = std::unique_ptr<Plane>(new Plane(object_type));
    }
  }

  // Getters
  struct Material& GetMaterial();
  Eigen::Matrix4f GetTransform();
  Sphere& GetSphere() { return *sphere_; }
  Plane& GetPlane() { return *plane_; }

  // Setters
  void SetTransform(Eigen::Matrix4f transform);
  void SetMaterial(struct Material material);

  // Wrapper function for NormalAtWorldPoint
  Eigen::Vector4f NormalAtLocalPoint(Eigen::Vector4f point);
  Eigen::Vector4f NormalAtWorldPoint(Eigen::Vector4f world_point);

  object_type::ObjectType& GetObjectType() { return object_type_; }

 private:
  std::shared_ptr<Sphere> sphere_;
  std::shared_ptr<Plane> plane_;
  object_type::ObjectType object_type_;
};