#pragma once
#include <vector>
#include "core/models/camera.h"
#include "core/models/world.h"
#include "core/visual/canvas.h"

// Render the world form camera
void Render(Camera& camera, World& world, Canvas* canvas) {
  // Uses the camera to render and image of the given world
  for (int y = 0; y < camera.GetHeight(); y++) {
    for (int x = 0; x < camera.GetWidth(); x++) {
      Ray ray;
      camera.RayToPixel(x, y, &ray);
      Eigen::Vector3f color = ray.ColorAt(world);
      canvas->WritePixel(y, x, color);
    }
  }
  std::cout << " Render completed/" << std::endl;
}