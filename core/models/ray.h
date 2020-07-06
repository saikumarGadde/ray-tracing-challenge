#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include "core/models/world.h"

// Intersection of a ray with the other objects in the world
struct Intersection {
  // Constructor with distance and object
  Intersection(float t, Object* object) : t_(t), object_(object) {}

  float GetT() { return t_; }

  Object* GetObject() { return object_; }

  // Object in the Intersection
  Object* object_;
  // T value of the intersection
  float t_;
  // Type of the object
  object_type::ObjectType object_type;
};

struct Comps {
  // Object of intersection
  Object* object;
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

  // Empty constructor
  Ray() {}

  // Position at a distance along the ray
  Eigen::Vector4f Position(const float distance) const;

  // Applies transform to a Ray
  void SetTransform(Eigen::Matrix4f& transformation_matrix);

  // Get Transformed origin and direction of the ray based on the transform
  // matrix of the object.
  void GetTransform(Eigen::Matrix4f& transform_matrix, Eigen::Vector4f* origin,
                    Eigen::Vector4f* direction);

  // Intersect a ray with a sphere
  void IntersectObject(Object& object);

  // Intersect a ray with a world
  void IntersectWorld(World& world);

  // Return origin
  Eigen::Vector4f GetOrigin() { return origin_; }

  // Sets origin of the ray vector
  void SetOrigin(Eigen::Vector4f origin) { origin_ = origin; }

  // Return direction
  Eigen::Vector4f GetDirection() { return direction_; }

  // Sets direction of the ray vector
  void SetDirection(Eigen::Vector4f direction) { direction_ = direction; }

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
  Eigen::Vector3f ShadeHit(World& world, struct Comps& comps);

  Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal);

  Eigen::Vector3f Lighting2(struct Material material,
                            struct PointLight point_light,
                            Eigen::Vector4f position, Eigen::Vector4f eyev,
                            Eigen::Vector4f normalv);

 private:
  // Origin of the ray
  Eigen::Vector4f origin_;
  // Direction of the ray
  Eigen::Vector4f direction_;
  // Intersections of the given ray
  std::vector<struct Intersection*> intersections_;
};