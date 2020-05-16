#pragma once
#include "core/protos/entities_3d.h"

struct Canvas {
  // Constructor for Canvas
  Canvas(uint64_t height, uint64_t width) : height(height), width(width) {}
  // Height of the canvas
  int height;
  // Width of the canvas
  int width;
  // Create a black color
  struct RGBColor black_color = {0, 0, 0};

  // Canvas creation
  // @TODO(Gadde) : Can also reverse the order height and width
  struct RGBColor canvas[height][width] = {black_color};
};