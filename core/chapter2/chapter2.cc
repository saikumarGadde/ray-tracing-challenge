#include "core/chapter2/chapter2.h"
#include <assert.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

struct RGBColor AddColors(struct RGBColor color1, struct RGBColor color2) {
  struct RGBColor color;
  color.r = color1.r + color2.r;
  color.g = color1.g + color2.g;
  color.b = color1.b + color2.b;
  return color;
}

struct RGBColor SubtractColors(struct RGBColor color1, struct RGBColor color2) {
  struct RGBColor color;
  color.r = color1.r - color2.r;
  color.g = color1.g - color2.g;
  color.b = color1.b - color2.b;
  return color;
}

struct RGBColor ScaleColor(struct RGBColor color1, float scale) {
  struct RGBColor color;
  color.r = color1.r * scale;
  color.g = color1.g * scale;
  color.b = color1.b * scale;
  return color;
}

// Multiplication of two colors
// "Hadamard Product" // "Schur Product"
struct RGBColor MultiplyColors(struct RGBColor color1, struct RGBColor color2) {
  struct RGBColor result_color;
  result_color.r = color1.r * color2.r;
  result_color.g = color1.g * color2.g;
  result_color.b = color1.b * color2.b;
  return result_color;
}