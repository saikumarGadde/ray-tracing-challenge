#pragma once
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include "core/ops/color_ops.h"

class Canvas {
 public:
  // Constructor for Canvas
  Canvas(uint64_t height, uint64_t width) : height_(height), width_(width) {
    for (int i = 0; i < height; i++) {
      std::vector<Eigen::Vector3f> rows(width, RGBColor(0, 0, 0));
      canvas_.push_back(rows);
    }
  };

  // Get height of the canvas
  uint64_t GetHeight() { return height_; };
  // Get width of the canvas
  uint64_t GetWidth() { return width_; };
  // Get the color of a canvas pixel
  Eigen::Vector3f GetPixel(uint64_t y, uint64_t x);
  // Write pixel in a canvas
  void WritePixel(uint64_t y, uint64_t x, Eigen::Vector3f color);
  // Write Canvas to PPM File
  void CanvasToPPM(const char ppm_file_path[]);
  // Read PPM File to a canvas
  void PPMToCanvas(const char ppm_file_path[]);

 private:
  // Two dimensional structure to store the colors of each pixel in 2D
  std::vector<std::vector<Eigen::Vector3f>> canvas_;

  // Store the height of the canvas over here
  const uint64_t height_;
  // Store the width of the canvas over here
  const uint64_t width_;
};