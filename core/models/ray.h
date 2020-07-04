#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "core/models/light.h"
#include "core/models/object.h"
#include "core/models/world.h"

// Intersection of a ray with the other objects in the world
struct Intersection {
  // Default constructor
  Intersection() {}

  // Constructor with distance and object
  Intersection(float t, struct Object object) : t_(t), object_(object) {}

  float GetT() { return t_; }

  struct Object GetObject() {
    return object_;
  }

  // Object in the Intersection
  struct Object object_;
  // T value of the intersection
  float t_;
  // Type of the object
  ObjectType object_type;
};

struct Comps {
  // Object of intersection
  struct Object object;
  // Intersection at a distance
  float t;
  // Precomputations
  Eigen::Vector4f point;
  // Eye vector
  Eigen::Vector4f eyev;
  // Normal Vecotr to the plane
  Eigen::Vector4f normalv;
  // The light is Inside the object or outside the object
  bool inside;
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

  struct Intersection* PopIntersection();

  struct Intersection* GetIntersection();

  void ClearIntersections() { intersections_.clear(); }

  // Function to add an intersection to list intersections_ with sorted order
  void AddIntersection(struct Intersection* intersection);

  // Prepare computations
  struct Comps PrepareComputations(struct Intersection intersection);

  // Returns the color ar an intersection point of the ray and the world
  Eigen::Vector3f ColorAt(World& world);

  // Shade Hit function
  Eigen::Vector3f ShadeHit(World world, struct Comps& comps);

 private:
  // Origin of the ray
  Eigen::Vector4f origin_;
  // Direction of the ray
  Eigen::Vector4f direction_;
  // Intersections of the given ray
  std::vector<struct Intersection*> intersections_;
  // Get Transformed origin and direction of the ray based on the transform
  // matrix of the object.
  void GetTransform(Eigen::Matrix4f transform_matrix, Eigen::Vector4f* origin,
                    Eigen::Vector4f* direction);
};