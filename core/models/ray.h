#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "core/models/object.h"
#include "core/models/sphere.h"
#include "core/models/world.h"

// Intersection of a ray with the other objects in the world
struct Intersection {
  // Default constructor
  Intersection() {}

  // Constructor with distance and object
  Intersection(float t, struct Object object) : t_(t), object_(object) {}

  // Object in the Intersection
  struct Object object_;
  // T value of the intersection
  float t_;
  // Type of the object
  ObjectType object_type;
};

class Ray {
 public:
  // Constructor for Ray class
  Ray(Eigen::Vector4f origin, Eigen::Vector4f direction)
      : origin_(origin), direction_(direction) {}

  // Position at a distance along the ray
  Eigen::Vector4f Position(const float distance) const;

  // Applies transform to a Ray
  void SetTransform(Eigen::Matrix4f transformation_matrix);

  // Intersect a ray with a sphere
  void IntersectObject(struct Object object);

  // Intersect a ray with a world
  void IntersectWorld(World world);

  // Return origin
  Eigen::Vector4f GetOrigin() { return origin_; }

  // Return direction
  Eigen::Vector4f GetDirection() { return direction_; }

  // Get Intersections
  std::vector<struct Intersection*>& GetIntersections() {
    return intersections_;
  }

  void ClearIntersections() { intersections_.clear(); }

 private:
  // Origin of the ray
  Eigen::Vector4f origin_;
  // Direction of the ray
  Eigen::Vector4f direction_;
  // Intersections of the given ray
  std::vector<struct Intersection*> intersections_;
  // Function to add an intersection to list intersections_ with sorted order
  void AddIntersection(struct Intersection* intersection);
};