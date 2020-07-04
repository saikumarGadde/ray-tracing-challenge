#include "core/models/vector.h"
#include "core/ops/vector_ops.h"
#include "gtest/gtest.h"

TEST(Chapter1Test, TestPoint1DimCreation) {
  // @TODO :: Test the point and Vector1Dim creation in this function.
  Eigen::Vector4f point = Point1Dim(4, -4, 3);
  EXPECT_EQ(point(0), 4);
  EXPECT_EQ(point(1), -4);
  EXPECT_EQ(point(2), 3);
  EXPECT_EQ(point(3), 1.0);

  Eigen::Vector4f vector = Vector1Dim(4, -4, 3);
  EXPECT_EQ(vector(0), 4);
  EXPECT_EQ(vector(1), -4);
  EXPECT_EQ(vector(2), 3);
  EXPECT_EQ(vector(3), 0.0);

  Eigen::Vector4f result = Point1Dim(3, -2, 5) + Vector1Dim(-2, 3, 1);
  EXPECT_EQ(result(0), 1);
  EXPECT_EQ(result(1), 1);
  EXPECT_EQ(result(2), 6);
  EXPECT_EQ(result(3), 1);

  // Subtracting two Point1Dims
  result = Point1Dim(3, 2, 1) - Point1Dim(5, 6, 7);
  EXPECT_EQ(result(0), -2.0f);
  EXPECT_EQ(result(1), -4.0f);
  EXPECT_EQ(result(2), -6.0f);
  EXPECT_EQ(result(3), 0.0f);

  // Subtracting a Point1Dim and a vector
  result = Point1Dim(3, 2, 1) - Vector1Dim(5, 6, 7);
  EXPECT_EQ(result(0), -2);
  EXPECT_EQ(result(1), -4);
  EXPECT_EQ(result(2), -6);
  EXPECT_EQ(result(3), 1);

  // Subtracting two vectors
  result = Vector1Dim(3, 2, 1) - Vector1Dim(5, 6, 7);
  EXPECT_EQ(result(0), -2);
  EXPECT_EQ(result(1), -4);
  EXPECT_EQ(result(2), -6);
  EXPECT_EQ(result(3), 0);

  // Negation unittest

  result = Negate(Vector1Dim(1, -2, 3));
  EXPECT_EQ(result(0), -1);
  EXPECT_EQ(result(1), 2);
  EXPECT_EQ(result(2), -3);
  EXPECT_EQ(result(3), 0);

  // Multiplication
  result = VectorScalarMultiply(Vector1Dim(1, -2, 3), 3.5);
  EXPECT_EQ(result(0), 3.5);
  EXPECT_EQ(result(1), -7);
  EXPECT_EQ(result(2), 10.5);
  EXPECT_EQ(result(3), 0);

  // Division
  result = VectorScalarDivide(Vector1Dim(1, -2, 3), 2.0);
  EXPECT_EQ(result(0), 0.5);
  EXPECT_EQ(result(1), -1);
  EXPECT_EQ(result(2), 1.5);
  EXPECT_EQ(result(3), 0);

  // Magnitude
  float result_magnitude = Magnitude(Vector1Dim(-1, -2, 3));
  EXPECT_NEAR(result_magnitude, sqrt(14), 0.0001);

  // Normalization
  result = Normalization(Vector1Dim(1, 2, 3));
  EXPECT_NEAR(result(0), 1.0 / sqrt(14), 0.00001);
  EXPECT_NEAR(result(1), 2.0 / sqrt(14), 0.00001);
  EXPECT_NEAR(result(2), 3.0 / sqrt(14), 0.00001);
  EXPECT_NEAR(result(3), 0, 0.00001);

  // DotProduct
  Eigen::Vector4f v7 = Vector1Dim(1, 2, 3);
  Eigen::Vector4f v8 = Vector1Dim(2, 3, 4);
  float dot_result = v7.dot(v8);
  EXPECT_FLOAT_EQ(dot_result, 20);

  // CrossProduct4f
  Eigen::Vector4f cp_result =
      CrossProduct4f(Vector1Dim(1, 2, 3), Vector1Dim(2, 3, 4));
  EXPECT_EQ(cp_result(0), -1);
  EXPECT_EQ(cp_result(1), 2);
  EXPECT_EQ(cp_result(2), -1);
  EXPECT_EQ(cp_result(3), 0);

  cp_result = CrossProduct4f(Vector1Dim(2, 3, 4), Vector1Dim(1, 2, 3));
  EXPECT_EQ(cp_result(0), 1);
  EXPECT_EQ(cp_result(1), -2);
  EXPECT_EQ(cp_result(2), 1);
  EXPECT_EQ(cp_result(3), 0);
};