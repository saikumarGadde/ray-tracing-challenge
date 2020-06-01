#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include "core/chapter2/chapter2.h"
#include "core/chapter4/chapter4.h"
#include "core/protos/entities_3d.h"
#include "core/protos/visualization_utils.h"

/**
  Important points from the book
  1. Most basic muscle in the body of a ray tracer - Ray Casting
  Ray-casting - Ray casting is the process of creating a ray, or line and
  finding the intersections of that ray with the objects in a scene.
*/

struct Ray {
  Ray(Eigen::Vector4f origin_, Eigen::Vector4f direction_)
      : origin(origin_), direction(direction_) {}
  // Store the origin, which is the starting point of the ray
  Eigen::Vector4f origin;
  // Store the vector, direction in which the ray points to
  Eigen::Vector4f direction;
};

// Material struct
struct Material {
  Material(Eigen::Vector3f rgb_color_, float ambient_, float diffuse_,
           float specular_, float shininess_)
      : rgb_color(rgb_color_),
        ambient(ambient_),
        diffuse(diffuse_),
        specular(specular_),
        shininess(shininess_) {}

  Material() {
    rgb_color(0) = 1;
    rgb_color(1) = 1;
    rgb_color(2) = 1;
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
  }

  Eigen::Vector3f rgb_color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
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
  // Material of the object
  struct Material material;
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

// Calculate the intersections
struct Intersection* Hit(struct Intersection* intersections[], int size);

// Travelling along the ray from the starting point
Eigen::Vector4f Position(const struct Ray ray, const float distance);

// Method to intersect the ray and sphere
std::vector<struct Intersection*> Intersect(struct Ray ray,
                                            struct Sphere sphere);

// Transformation with a transformation matrix and vector or ray
struct Ray Transform(Eigen::Matrix4f& transform_matrix, struct Ray ray);

// Putting it together
void Chapter5Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path);

float Magnitude(Eigen::Vector4f& vector);

// Normalization of the point
Eigen::Vector4f Normalization(Eigen::Vector4f vector);
