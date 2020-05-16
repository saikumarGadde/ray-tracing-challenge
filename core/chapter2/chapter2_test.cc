#include "core/chapter2/chapter2.h"
#include "gtest/gtest.h"

TEST(Chapter2Test, CanvasCreation) {
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