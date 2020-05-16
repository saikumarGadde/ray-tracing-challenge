#pragma once

// Tuple which can store 3d entities like a point or vector
struct Tuple4 {
  // X coordinate
  float x;
  // Y coordinate
  float y;
  // X coordinate
  float z;
  // differentiator between a point and a vector
  float w;
};

struct RGBColor {
  // Red color between 0 and 1
  float r;
  // Green color between 0 and 1
  float g;
  // Blue color between 0 and 1
  float b;
};