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
    inner_sphere.transform = Scaling(0.5, 0.5, 0.5);
    // Set material of outer sphere
    struct Material outer_sphere_material(Color(0.8, 1.0, 0.6), 0.1, 0.7, 0.2,
                                          200.0);
    outer_sphere.material = outer_sphere_material;
    light.intensity = Color(1, 1, 1);
    light.point = Point1Dim(-10, -10, -10);
  }
  // Two spheres at origin
  struct Sphere inner_sphere;
  struct Sphere outer_sphere;
  // Point light
  struct PointLight light;
};
