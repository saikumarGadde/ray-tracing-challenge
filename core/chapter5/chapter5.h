#pragma once
#define _USE_MATH_DEFINES
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
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
  // Store the center fo the sphere
  Eigen::Vector4f center;
  center <<
      // Store the radius of the Sphere
      float radius;
};

// Travelling along the ray from the starting point
Eigen::Vector4f Position(struct Ray ray, float distance);

// Method to intersect the ray and sphere
void Intersect(struct Ray ray, struct Sphere sphere);