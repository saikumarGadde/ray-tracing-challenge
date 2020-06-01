#include "TheRayTracerChallenge/chapter1/chapter1.h"
#include "gtest/gtest.h"

namespace chapter1 {

TEST(Chapter1Test, TestPointCreation) {
  // @TODO :: Test the point and vector creation in this function.
  Tuple4 point = Point(4, -4, 3);
  EXPECT_EQ(point.x, 4);
  EXPECT_EQ(point.y, -4);
  EXPECT_EQ(point.z, 3);
  EXPECT_EQ(point.w, 1.0);

  Tuple4 vector = Vector(4, -4, 3);
  EXPECT_EQ(vector.x, 4);
  EXPECT_EQ(vector.y, -4);
  EXPECT_EQ(vector.z, 3);
  EXPECT_EQ(vector.w, 0.0);

  Tuple4 a1 = Point(3, -2, 5);
  Tuple4 a2 = Vector(-2, 3, 1);
  Tuple4 result1 = add(a1, a2);
  EXPECT_EQ(result1.x, 1);
  EXPECT_EQ(result1.y, 1);
  EXPECT_EQ(result1.z, 6);
  EXPECT_EQ(result1.w, 1);

  // Subtracting two points
  Tuple4 p1 = Point(3, 2, 1);
  Tuple4 p2 = Point(5, 6, 7);
  Tuple4 result2 = subtract(p1, p2);
  EXPECT_EQ(result2.x, -2);
  EXPECT_EQ(result2.y, -4);
  EXPECT_EQ(result2.z, -6);
  EXPECT_EQ(result2.w, 0);

  // Subtracting a point and a vector
  Tuple4 p = Point(3, 2, 1);
  Tuple4 v = Vector(5, 6, 7);
  Tuple4 result3 = subtract(p, v);
  EXPECT_EQ(result3.x, -2);
  EXPECT_EQ(result3.y, -4);
  EXPECT_EQ(result3.z, -6);
  EXPECT_EQ(result3.w, 1);

  // Subtracting two vectors
  Tuple4 v1 = Vector(3, 2, 1);
  Tuple4 v2 = Vector(5, 6, 7);
  Tuple4 result4 = subtract(v1, v2);
  EXPECT_EQ(result4.x, -2);
  EXPECT_EQ(result4.y, -4);
  EXPECT_EQ(result4.z, -6);
  EXPECT_EQ(result4.w, 0);

  // Negation unittest
  Tuple4 n1 = Vector(1, -2, 3);
  Tuple4 result5 = Negate(n1);
  EXPECT_EQ(result5.x, -1);
  EXPECT_EQ(result5.y, 2);
  EXPECT_EQ(result5.z, -3);
  EXPECT_EQ(result5.w, 0);

  // Multiplication
  Tuple4 n2 = Vector(1, -2, 3);
  Tuple4 result6 = Multiply(n2, 3.5);
  EXPECT_EQ(result6.x, 3.5);
  EXPECT_EQ(result6.y, -7);
  EXPECT_EQ(result6.z, 10.5);
  EXPECT_EQ(result6.w, 0);

  // Division
  Tuple4 n3 = Vector(1, -2, 3);
  Tuple4 result7 = Division(n3, 2);
  EXPECT_EQ(result7.x, 0.5);
  EXPECT_EQ(result7.y, -1);
  EXPECT_EQ(result7.z, 1.5);
  EXPECT_EQ(result7.w, 0);

  // Magnitude
  Tuple4 v5 = Vector(-1, -2, 3);
  float result8 = Magnitude(v5);
  float result9 = sqrt(14);
  EXPECT_EQ(result8, result9);

  // Normalization
  Tuple4 v6 = Vector(1, 2, 3);
  Tuple4 result10 = Normalization(v6);
  float x = 1.0 / sqrt(14);
  float y = 2.0 / sqrt(14);
  float z = 3.0 / sqrt(14);
  std::cout << "x " << result10.x << "  y: " << result10.y
            << "  z is : " << result10.z << std::endl;
  EXPECT_EQ(result10.x, x);
  EXPECT_EQ(result10.y, y);
  // EXPECT_EQ(result10.z, z);
  EXPECT_EQ(result10.w, 0);

  // DotProduct
  Tuple4 v7 = Vector(1, 2, 3);
  Tuple4 v8 = Vector(2, 3, 4);
  float dot_result = DotProduct(v7, v8);
  EXPECT_EQ(dot_result, 20);

  // CrossProduct
  Tuple4 v9 = Vector(1, 2, 3);
  Tuple4 v10 = Vector(2, 3, 4);
  struct Tuple4 cp_result = CrossProduct(v9, v10);
  EXPECT_EQ(cp_result.x, -1);
  EXPECT_EQ(cp_result.y, 2);
  EXPECT_EQ(cp_result.z, -1);
  EXPECT_EQ(cp_result.w, 0);

  cp_result = CrossProduct(v10, v9);
  EXPECT_EQ(cp_result.x, 1);
  EXPECT_EQ(cp_result.y, -2);
  EXPECT_EQ(cp_result.z, 1);
  EXPECT_EQ(cp_result.w, 0);
};

}  // namespace chapter1