
#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>

// Create color in RGB Color space
Eigen::Vector3f RGBColor(float r, float g, float b);

// Create color in HSV Color space
Eigen::Vector3f HSVColor(float h, float s, float v);

// Sum of two RGB Colors
Eigen::Vector3f RGBColorSum(Eigen::Vector3f color1, Eigen::Vector3f color2);

// Multiplication of two RGB Colors
Eigen::Vector3f RGBColorMultiply(Eigen::Vector3f color1,
                                 Eigen::Vector3f color2);

// Difference of two colors
Eigen::Vector3f SubtractColors(Eigen::Vector3f color1, Eigen::Vector3f color2);

Eigen::Vector3f ScaleColor(Eigen::Vector3f color1, float scale);
/**
 * Multiplication of two colors
 * This color product is called as "Hadamard Product" // "Schur Product"
 * C1*C2 results in a color where a C1 colored light is projected onto a
 * C2 colored object.
 */
// "Hadamard Product" // "Schur Product"
Eigen::Vector3f MultiplyColors(Eigen::Vector3f color1, Eigen::Vector3f color2);
