#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include "TheRayTracerChallenge/chapter6/chapter6.h"

// World data structure
class World {
 public:
  //   // Default Constructor for the World
  World() {
    // Set transform of inner sphere
    struct Sphere inner_sphere;
    inner_sphere.transform = Scaling(0.5, 0.5, 0.5);
    objects.push_back(Object(inner_sphere));
    // Set material of outer sphere
    struct Material outer_sphere_material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2,
                                          200.0);
    struct Sphere outer_sphere;
    outer_sphere.material = outer_sphere_material;
    objects.push_back(Object(outer_sphere));

    light.intensity = Color(1, 1, 1);
    light.point = Point1Dim(-10, -10, -10);
  }

  void AddObject(struct Object object) {
    // Add object to the objects vector
    objects.push_back(object);
  }

  // Point light
  struct PointLight light;
  // Vector of objects in the world
  std::vector<struct Object> objects;
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

// Method to intersect the ray and the world
std::vector<struct Intersection*> Intersect(struct Ray ray, struct World world);

// Prepare computations
struct Comps PrepareComputations(struct Intersection intersection,
                                 struct Ray ray);

// Shade hit function
Eigen::Vector3f ShadeHit(struct World world, struct Comps comps);
