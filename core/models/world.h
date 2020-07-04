#pragma once
#include <vector>
#include "core/models/light.h"
#include "core/models/material.h"
#include "core/models/object.h"
#include "core/models/sphere.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/transformations.h"

// World data structure
class World {
 public:
  // Default Constructor for the World
  World() {
    // Add First object
    // Set transform of inner sphere
    Sphere inner_sphere;
    inner_sphere.SetTransform(Scaling(0.5, 0.5, 0.5));
    struct Object object1(inner_sphere);
    AddObject(object1);

    // Add second object
    // Set material of outer sphere
    Sphere outer_sphere;
    struct Material outer_sphere_material(RGBColor(0.8, 1.0, 0.6), 0.1, 0.7,
                                          0.2, 200.0);
    outer_sphere.SetMaterial(outer_sphere_material);
    struct Object object2(outer_sphere);
    AddObject(object2);

    struct PointLight light;
    light.SetIntensity(RGBColor(1, 1, 1));
    light.SetLightPosition(Point1Dim(-10, -10, -10));
    AddLight(light);
  }

  // Get objects present in the World
  std::vector<struct Object>& GetObjects();

  // Add an object to the world
  void AddObject(struct Object object);

  // Add a light to the world
  void AddLight(struct PointLight point_light);

  // Get the point light of the world
  struct PointLight GetLight();

  void SetLight(struct PointLight point_light, int index);

 private:
  // Point lights present in the world
  std::vector<struct PointLight> point_lights_;
  // Vector of objects in the world
  std::vector<struct Object> objects_;
};
