#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include "core/models/material.h"
#include "core/models/sphere.h"

class Object : public Sphere {
 public:
  Object(object_type::ObjectType object_type) : Sphere(object_type) {
    // Constructor
    if (object_type == object_type::ObjectType::SPHERE) {
      InitSphere();
    }
  };
};