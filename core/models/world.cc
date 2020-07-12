#include "core/models/world.h"

void World::AddObject(Object& object) {
  // Add objects to the class
  objects_.push_back(object);
}

void World::AddLight(struct PointLight& point_light) {
  // Add point light to the world class
  point_lights_.push_back(point_light);
}

// Get the objects present in the world
std::vector<Object>& World::GetObjects() {
  // Return the objects present in the world
  return objects_;
}

struct PointLight World::GetLight() {
  return point_lights_[0];
}

void World::SetLight(struct PointLight point_light, int index) {
  point_lights_[index] = point_light;
}