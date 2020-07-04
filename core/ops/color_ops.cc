#include "core/ops/color_ops.h"

// Create color in RGB Color space
Eigen::Vector3f RGBColor(float r, float g, float b) {
  Eigen::Vector3f color;
  color(0) = r;
  color(1) = g;
  color(2) = b;
  return color;
}

// Create color in HSV Color space
Eigen::Vector3f HSVColor(float h, float s, float v) {
  Eigen::Vector3f color;
  color(0) = h;
  color(1) = s;
  color(2) = v;
  return color;
}

Eigen::Vector3f RGBColorSum(Eigen::Vector3f color1, Eigen::Vector3f color2) {
  Eigen::Vector3f color;
  color(0) = std::min(1.0f, color1(0) + color2(0));
  color(1) = std::min(1.0f, color1(1) + color2(1));
  color(2) = std::min(1.0f, color1(2) + color2(2));
  return color;
}

Eigen::Vector3f RGBColorMultiply(Eigen::Vector3f color1,
                                 Eigen::Vector3f color2) {
  Eigen::Vector3f color;
  color(0) = color1(0) * color2(0);
  color(1) = color1(1) * color2(1);
  color(2) = color1(2) * color2(2);
  return color;
}

// Difference of two colors
Eigen::Vector3f SubtractColors(Eigen::Vector3f color1, Eigen::Vector3f color2) {
  return color1 - color2;
}

Eigen::Vector3f ScaleColor(Eigen::Vector3f color1, float scale) {
  return color1 * scale;
}

/**
 * Multiplication of two colors
 * This color product is called as "Hadamard Product" // "Schur Product"
 * C1*C2 results in a color where a C1 colored light is projected onto a
 * C2 colored object.
 */
// "Hadamard Product" // "Schur Product"
Eigen::Vector3f MultiplyColors(Eigen::Vector3f color1, Eigen::Vector3f color2) {
  Eigen::Vector3f result_color;
  result_color(0) = color1(0) * color2(0);
  result_color(1) = color1(1) * color2(1);
  result_color(2) = color1(2) * color2(2);
  return result_color;
}
