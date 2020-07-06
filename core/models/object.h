#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/material.h"
#include "core/models/sphere.h"

// Object struct
class Object : public Sphere {
 public:
  // Constructor with object type from the above enum ObjectType
  Object(object_type::ObjectType object_type)
      : Sphere(object_type), object_type_(object_type) {}

  object_type::ObjectType GetObjectType() {
    // Return the Object Type
    return object_type_;
  }

  object_type::ObjectType object_type_;
};