#include "TheRayTracerChallenge/chapter2/chapter2.h"
#include "core/protos/visualization_utils.h"
#include "gtest/gtest.h"

TEST(Chapter2Test, TestColorOperators) {
  // Test for color creation using struct RGBColor
  float r = -0.5;
  float g = 0.4;
  float b = 1.7;
  RGBColor rgb_color{r, g, b};
  EXPECT_EQ(rgb_color.r, r);
  EXPECT_EQ(rgb_color.g, g);
  EXPECT_EQ(rgb_color.b, b);

  // Sum of colors
  struct RGBColor rgb1 = {0.9, 0.6, 0.75};
  struct RGBColor rgb2 = {0.7, 0.1, 0.25};
  struct RGBColor result = AddColors(rgb1, rgb2);
  EXPECT_FLOAT_EQ(result.r, 1.6);
  EXPECT_FLOAT_EQ(result.g, 0.7);
  EXPECT_FLOAT_EQ(result.b, 1.0);

  // Subtraction of colors
  struct RGBColor result2 = SubtractColors(rgb1, rgb2);
  EXPECT_FLOAT_EQ(result2.r, 0.2);
  EXPECT_FLOAT_EQ(result2.g, 0.5);
  EXPECT_FLOAT_EQ(result2.b, 0.5);

  // Testing ScaleColor
  struct RGBColor result3 = ScaleColor(rgb1, 2);
  EXPECT_FLOAT_EQ(result3.r, 1.8);
  EXPECT_FLOAT_EQ(result3.g, 1.2);
  EXPECT_FLOAT_EQ(result3.b, 1.5);

  // Multiplying two colors
  struct RGBColor result4 = MultiplyColors(rgb1, rgb2);
  EXPECT_FLOAT_EQ(result4.r, 0.63);
  EXPECT_FLOAT_EQ(result4.g, 0.06);
  EXPECT_FLOAT_EQ(result4.b, 0.1875);
};

TEST(Chapter2Test, TestCanvasCreation) {
  // Test Canvas creation
  uint64_t height = 100;
  uint64_t width = 100;
  Canvas canvas(height, width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      EXPECT_EQ(canvas.canvas[i][j].r, 0);
      EXPECT_EQ(canvas.canvas[i][j].g, 0);
      EXPECT_EQ(canvas.canvas[i][j].b, 0);
    }
  }

  // Test WritePixel value to Canvas in C++
  float r = 1.0;
  float g = 0.67;
  float b = 0.23;
  struct RGBColor new_color = {r, g, b};
  WritePixel(canvas, 2, 3, new_color);
  EXPECT_EQ(canvas.canvas[2][3].r, r);
  EXPECT_EQ(canvas.canvas[2][3].g, g);
  EXPECT_EQ(canvas.canvas[2][3].b, b);

  // Test to write the PPM File
  const char ppm_file_path[] = "/Users/gaddekumar/test.ppm";
  CanvasToPPM(canvas, ppm_file_path);

  // Test
  Canvas canvas2(5, 3);
  struct RGBColor color1 = {1.5, 0, 0};
  struct RGBColor color2 = {0, 0.5, 0};
  struct RGBColor color3 = {-0.5, 0, 1};
  canvas2.set_pixel_color(0, 0, color1);
  canvas2.set_pixel_color(2, 1, color2);
  canvas2.set_pixel_color(4, 2, color3);
  // Write the canvas2 to a PPM file
  CanvasToPPM(canvas2, ppm_file_path);
};
