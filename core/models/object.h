#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/sphere.h"

// Object type sphere, cone or random
enum ObjectType {
  RANDOM = 0,
  SPHERE = 1,
  CONE = 2,
};

// Object struct
struct Object {
  Object() {
    // Set object type to random where the World can contain all types of
    // objects
    object_type = ObjectType::RANDOM;
  }

  Object(struct Sphere sphere_) : sphere(sphere_) {
    object_type = ObjectType::SPHERE;
  }
  struct Sphere sphere;
  ObjectType object_type;
};