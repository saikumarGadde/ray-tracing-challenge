#pragma once
#include <stdint.h>
#include <stdio.h>
#include <vector>

struct Canvas {
  // Constructor for Canvas
  Canvas(uint64_t height, uint64_t width) : height(height), width(width) {
    // Initialize a canvas with black color
    for (int i = 0; i < height; i++) {
      struct RGBColor black_color = {0, 0, 0};
      std::vector<struct RGBColor> rows(width, black_color);
      canvas.push_back(rows);
    }
  }

  // // Constructor to create canvas from a PPM File
  // Canvas(const char ppm_file_path[]) {
  //   // @TODO :: You have to read the ppm file over here and obtain the
  //   height,
  //   // width and also initialize over here.
  // }

  // Set color of a pixel in a Canvas object
  void set_pixel_color(uint64_t h, uint64_t w, struct RGBColor rgb_color) {
    canvas[h][w] = rgb_color;
  };

  // Two dimensional structure to store the colors of each pixel in 2D
  std::vector<std::vector<struct RGBColor>> canvas;
  // Store the height of the canvas over here
  const uint64_t height;
  // Store the width of the canvas over here
  const uint64_t width;
};