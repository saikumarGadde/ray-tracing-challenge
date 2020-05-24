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

// Add color to a pixel in canvas
void WritePixel(struct Canvas& canvas, uint64_t height, uint64_t width,
                struct RGBColor color) {
  // Assign the color value to the pixel
  canvas.canvas[height][width] = color;
}

// Store the canvas to a PPM file
void CanvasToPPM(struct Canvas& canvas, const char ppm_file_path[]) {
  // Open a PPM file
  FILE* fp = fopen(ppm_file_path, "w");
  // Write header to the PPM File
  fprintf(fp, "P3\n%d %d\n255\n", canvas.height, canvas.width);

  int r;
  int g;
  int b;
  int r_count;
  int g_count;
  int b_count;
  for (int i = 0; i < canvas.height; i++) {
    int count = 0;
    for (int j = 0; j < canvas.width; j++) {
      struct RGBColor pixel_color = canvas.canvas[i][j];
      r = std::max(0, std::min((int)(pixel_color.r * 255), 255));
      g = std::max(0, std::min((int)(pixel_color.g * 255), 255));
      b = std::max(0, std::min((int)(pixel_color.b * 255), 255));
      r_count = NumberOfDigitsInInteger(r) + 1;
      g_count = NumberOfDigitsInInteger(g) + 1;
      b_count = NumberOfDigitsInInteger(b) + 1;
      // Write the r, g, and b values to the PPM File
      // if the length of the line is less than some number, just push it to the
      // next line
      if (70 - count >= 4) {
        fprintf(fp, "%d ", r);
        count += r_count;
      } else {
        fprintf(fp, "\n");
        fprintf(fp, "%d ", r);
        count = r_count;
      }
      if (70 - count >= 4) {
        fprintf(fp, "%d ", g);
        count += g_count;
      } else {
        fprintf(fp, "\n");
        fprintf(fp, "%d ", g);
        count = g_count;
      }
      if (70 - count >= 4) {
        fprintf(fp, "%d ", b);
        count += b_count;
      } else {
        fprintf(fp, "\n");
        fprintf(fp, "%d ", b);
        count = b_count;
      }
    }
    fprintf(fp, "\n");
  }
  // Close the PPM File
  fclose(fp);
}

void PPMToCanvas(const char ppm_file_path[]) {
  // Open the PPM File
  FILE* fp = fopen(ppm_file_path, "r");
  // if (!fp) {
  //   std::cout << "Unable to open the file" << std::endl;
  // }
  // // Create a canvas object from the PPM File

  // // @TODO :: You have to read the header of the PPM File.

  // // @TODO :: Have to pass the height and width over here
  // Canvas canvas();
}