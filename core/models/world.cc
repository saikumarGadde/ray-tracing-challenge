#include "core/models/world.h"

void World::AddObject(struct Object object) {
  //
  objects_.push_back(object);
}

void World::AddLight(struct PointLight point_light) {
  // Add point light to the world class
  point_lights_.push_back(point_light);
}

// Get the objects present in the world
std::vector<struct Object>& World::GetObjects() {
  // Return the objects present in the world
  return objects_;
}