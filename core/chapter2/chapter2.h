#pragma once

#include <stdint.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
#include <string>
#include "core/chapter1/chapter1.h"
#include "core/protos/visualization_utils.h"

// Create a color over here
struct RGBColor AddColors(struct RGBColor color1, struct RGBColor color2);

// Difference of two colors
struct RGBColor SubtractColors(struct RGBColor color1, struct RGBColor color2);

// Multiplication of color with a scalar
struct RGBColor ScaleColor(struct RGBColor color1, float scale);

/**
 * Multiplication of two colors
 * This color product is called as "Hadamard Product" // "Schur Product"
 * C1*C2 results in a color where a C1 colored light is projected onto a
 * C2 colored object.
 */
struct RGBColor MultiplyColors(struct RGBColor color1, struct RGBColor color2);

void WritePixel(struct Canvas& canvas, uint64_t height, uint64_t width,
                struct RGBColor color);

// Store the canvas to a PPM file
void CanvasToPPM(struct Canvas& canvas, const char ppm_file_path[]);

// Count number of digits in an integer
int NumberOfDigitsInInteger(int number);

// Read the PPM File to a variable
void PPMToCanvas(const char ppm_file_path[]);