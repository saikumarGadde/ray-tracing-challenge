#pragma once
#include <vector>
#include "core/models/light.h"
#include "core/models/object.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/transformations.h"

// World data structure
class World {
 public:
  // Default Constructor for the World
  World(bool default_world) {
    if (default_world) {
      // Add First object
      // Set transform of inner sphere
      Object inner_sphere(object_type::ObjectType::SPHERE);
      inner_sphere.SetTransform(Scaling(0.5, 0.5, 0.5));
      AddObject(inner_sphere);

      // Add second object
      // Set material of outer sphere
      Object outer_sphere(object_type::ObjectType::SPHERE);
      struct Material outer_sphere_material(RGBColor(0.8, 1.0, 0.6), 0.1, 0.7,
                                            0.2, 200.0);
      outer_sphere.SetMaterial(outer_sphere_material);
      AddObject(outer_sphere);

      struct PointLight light;
      light.SetIntensity(RGBColor(1, 1, 1));
      light.SetLightPosition(Point1Dim(-10, 10, -10));
      AddLight(light);
    }
  };

  // Get objects present in the World
  std::vector<Object>& GetObjects();

  // Add an object to the world
  void AddObject(Object object);

  // Add a light to the world
  void AddLight(struct PointLight point_light);

  // Get the point light of the world
  struct PointLight GetLight();

  void SetLight(struct PointLight point_light, int index);

 private:
  // Point lights present in the world
  std::vector<struct PointLight> point_lights_;
  // Vector of objects in the world
  std::vector<Object> objects_;
};
