#include "core/ops/color_ops.h"
#include "core/visual/canvas.h"
#include "gtest/gtest.h"

TEST(Chapter2Test, TestColorOperators) {
  // Test for color creation using struct RGBColor
  Eigen::Vector3f rgb_color = RGBColor(-0.5, 0.4, 1.7);
  EXPECT_EQ(rgb_color(0), -0.5f);
  EXPECT_EQ(rgb_color(1), 0.4f);
  EXPECT_EQ(rgb_color(2), 1.7f);

  // Sum of colors
  auto result = RGBColorSum(RGBColor(0.9, 0.6, 0.75), RGBColor(0.7, 0.1, 0.25));
  EXPECT_FLOAT_EQ(result(0), 1.0);
  EXPECT_FLOAT_EQ(result(1), 0.7);
  EXPECT_FLOAT_EQ(result(2), 1.0);

  // Subtraction of colors
  auto result2 =
      SubtractColors(RGBColor(0.9, 0.6, 0.75), RGBColor(0.7, 0.1, 0.25));
  EXPECT_FLOAT_EQ(result2(0), 0.2);
  EXPECT_FLOAT_EQ(result2(1), 0.5);
  EXPECT_FLOAT_EQ(result2(2), 0.5);

  // Testing ScaleColor
  auto result3 = ScaleColor(RGBColor(0.9, 0.6, 0.75), 2);
  EXPECT_FLOAT_EQ(result3(0), 1.8);
  EXPECT_FLOAT_EQ(result3(1), 1.2);
  EXPECT_FLOAT_EQ(result3(2), 1.5);

  // Multiplying two colors
  auto result4 =
      MultiplyColors(RGBColor(0.9, 0.6, 0.75), RGBColor(0.7, 0.1, 0.25));
  EXPECT_FLOAT_EQ(result4(0), 0.63);
  EXPECT_FLOAT_EQ(result4(1), 0.06);
  EXPECT_FLOAT_EQ(result4(2), 0.1875);
};

TEST(Chapter2Test, TestCanvasCreation) {
  // Test Canvas creation
  Canvas canvas(100, 100);
  for (int y = 0; y < 100; y++) {
    for (int x = 0; x < 100; x++) {
      Eigen::Vector3f rgb_color = canvas.GetPixel(y, x);
      EXPECT_EQ(rgb_color(0), 0);
      EXPECT_EQ(rgb_color(1), 0);
      EXPECT_EQ(rgb_color(2), 0);
    }
  }
  // Test WritePixel value to Canvas in C++
  canvas.WritePixel(2, 3, RGBColor(1.0, 0.67, 0.23));
  Eigen::Vector3f color_result = canvas.GetPixel(2, 3);
  EXPECT_EQ(color_result(0), 1.0f);
  EXPECT_EQ(color_result(1), 0.67f);
  EXPECT_EQ(color_result(2), 0.23f);

  // Test to write the PPM File
  const char ppm_file_path[] = "/Users/gaddekumar/Desktop/test.ppm";
  canvas.CanvasToPPM(ppm_file_path);

  // Test
  Canvas canvas2(5, 3);
  canvas2.WritePixel(0, 0, RGBColor(1.5, 0, 0));
  canvas2.WritePixel(2, 1, RGBColor(0, 0.5, 0));
  canvas2.WritePixel(4, 2, RGBColor(-0.5, 0, 1));
  // Write the canvas2 to a PPM file
  canvas2.CanvasToPPM(ppm_file_path);
};
