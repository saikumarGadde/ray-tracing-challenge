#pragma once
#define _USE_MATH_DEFINES
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include "core/chapter4/chapter4.h"
/**
  Important points from the book
  1. Most basic muscle in the body of a ray tracer - Ray Casting
  Ray-casting - Ray casting is the process of creating a ray, or line and
  finding the intersections of that ray with the objects in a scene.
*/

struct Ray {
  Ray(Eigen::Vector4f& origin_, Eigen::Vector4f& direction_)
      : origin(origin_), direction(direction_) {}
  // Store the origin, which is the starting point of the ray
  Eigen::Vector4f origin;
  // Store the vector, direction in which the ray points to
  Eigen::Vector4f direction;
};

// Struct of the Sphere
struct Sphere {
  // Constructor of the Sphere with a center and radius
  Sphere(Eigen::Vector4f& center_, float radius_)
      : center(center_), radius(radius_) {}

  Sphere() {
    center << 0.0f, 0.0f, 0.0f, 1.0f;
    radius = 1;
    transform = Eigen::Matrix4f::Identity();
  }
  // Store the center fo the sphere
  Eigen::Vector4f center;
  // Store the radius of the Sphere
  float radius;
  // transform of the sphere object
  Eigen::Matrix4f transform;
};

enum ObjectType {
  SPHERE = 0,
  CONE = 1,
};

struct Intersection {
  // Constructor to create an intersection with distance along the ray and
  // the type of the object
  Intersection(float t_, struct Sphere& sphere_) : t(t_), sphere(sphere_) {
    // Set the type of the object over here
    object_type = ObjectType::SPHERE;
  }

  // Object that was intersected
  struct Sphere& sphere;
  // T value of the intersection
  float t;
  // Type of the object
  ObjectType object_type;
};

struct Intersection* Hit(struct Intersection* intersections[], int size);
// Travelling along the ray from the starting point
Eigen::Vector4f Position(const struct Ray ray, const float distance);
// Method to intersect the ray and sphere
std::vector<struct Intersection*> Intersect(struct Ray ray,
                                            struct Sphere sphere);
// Transformation with a transformation matrix and vector or ray
struct Ray Transform(Eigen::Matrix4f& transform_matrix, struct Ray ray);