#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/vector.h"
#include "core/ops/transformations.h"
#include "gtest/gtest.h"

TEST(Chapter4Test, TestMatrixOperators) {
  // Testing translation of a point with Matrix4f translation matrix
  Eigen::Matrix4f translation_matrix = Translation(5, -3, 2);
  Eigen::Vector4f point = Point1Dim(-3, 4, 5);

  Eigen::Vector4f result = translation_matrix * point;
  EXPECT_EQ(result[0], 2.0f);
  EXPECT_EQ(result[1], 1.0f);
  EXPECT_EQ(result[2], 7.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = translation_matrix.inverse() * point;
  EXPECT_EQ(result[0], -8.0f);
  EXPECT_EQ(result[1], 7.0f);
  EXPECT_EQ(result[2], 3.0f);
  EXPECT_EQ(result[3], 1.0f);

  Eigen::Vector4f vector = Vector1Dim(-3, 4, 5);
  result = translation_matrix * vector;
  EXPECT_EQ(result[0], -3.0f);
  EXPECT_EQ(result[1], 4.0f);
  EXPECT_EQ(result[2], 5.0f);
  EXPECT_EQ(result[3], 0.0f);

  // Test scaling
  Eigen::Matrix4f scaling_matrix = Scaling(2, 3, 4);
  Eigen::Vector4f point2 = Point1Dim(-4, 6, 8);
  Eigen::Vector4f result2 = scaling_matrix * point2;
  EXPECT_EQ(result2[0], -8.0f);
  EXPECT_EQ(result2[1], 18.0f);
  EXPECT_EQ(result2[2], 32.0f);
  EXPECT_EQ(result2[3], 1.0f);

  Eigen::Vector4f vector2 = Vector1Dim(-4, 6, 8);
  result2 = scaling_matrix * vector2;
  EXPECT_EQ(result2[0], -8.0f);
  EXPECT_EQ(result2[1], 18.0f);
  EXPECT_EQ(result2[2], 32.0f);
  EXPECT_EQ(result2[3], 0.0f);

  result2 = scaling_matrix.inverse() * vector2;
  EXPECT_EQ(result2[0], -2.0f);
  EXPECT_EQ(result2[1], 2.0f);
  EXPECT_EQ(result2[2], 2.0f);
  EXPECT_EQ(result2[3], 0.0f);

  // Test Reflection using the scaling_matrix
  Eigen::Matrix4f reflection_matrix = Scaling(-1, -1, -1);
  result2 = reflection_matrix * point2;
  EXPECT_EQ(result2[0], -point2[0]);
  EXPECT_EQ(result2[1], -point2[1]);
  EXPECT_EQ(result2[2], -point2[2]);
  EXPECT_EQ(result2[3], point2[3]);

  // Rotation along the X Axis
  Eigen::Vector4f point3 = Point1Dim(0, 1, 0);
  Eigen::Matrix4f half_quarter = RotationX(M_PI / 4);
  Eigen::Vector4f point3_result = half_quarter * point3;
  EXPECT_EQ(point3_result[0], 0.0f);
  EXPECT_EQ(point3_result[1], (float)(sqrt(2) / 2));
  EXPECT_EQ(point3_result[2], (float)(sqrt(2) / 2));
  EXPECT_EQ(point3_result[3], 1.0f);

  // Inverse of the rotation matrix gives the rotation in opposite direction
  point3_result = half_quarter.inverse() * point3;
  EXPECT_EQ(point3_result[0], 0.0f);
  EXPECT_FLOAT_EQ(point3_result[1], (float)(sqrt(2) / 2.0));
  EXPECT_FLOAT_EQ(point3_result[2], (float)(-sqrt(2) / 2.0));
  EXPECT_EQ(point3_result[3], 1.0f);

  // Test rotation around the Y Axis
  half_quarter = RotationY(M_PI / 4);
  Eigen::Vector4f point4 = Point1Dim(0, 0, 1);
  point3_result = half_quarter * point4;
  EXPECT_FLOAT_EQ(point3_result[0], (float)(sqrt(2) / 2.0));
  EXPECT_FLOAT_EQ(point3_result[1], 0.0f);
  EXPECT_FLOAT_EQ(point3_result[2], (float)(sqrt(2) / 2.0));
  EXPECT_FLOAT_EQ(point3_result[3], 1.0f);

  // Test rotation around the Z Axis
  half_quarter = RotationZ(M_PI / 4);
  point3_result = half_quarter * point3;
  EXPECT_FLOAT_EQ(point3_result[0], (float)(-sqrt(2) / 2.0));
  EXPECT_FLOAT_EQ(point3_result[1], (float)(sqrt(2) / 2.0));
  EXPECT_FLOAT_EQ(point3_result[2], 0.0f);
  EXPECT_FLOAT_EQ(point3_result[3], 1.0f);

  // Test shearing matrix
  Eigen::Matrix4f shearing_matrix = Shearing(1, 0, 0, 0, 0, 0);
  Eigen::Vector4f point5 = Point1Dim(2, 3, 4);
  Eigen::Vector4f point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 5.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 3.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 4.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);

  shearing_matrix = Shearing(0, 1, 0, 0, 0, 0);
  point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 6.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 3.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 4.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);

  shearing_matrix = Shearing(0, 0, 1, 0, 0, 0);
  point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 2.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 5.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 4.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);

  shearing_matrix = Shearing(0, 0, 0, 1, 0, 0);
  point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 2.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 7.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 4.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);

  shearing_matrix = Shearing(0, 0, 0, 0, 1, 0);
  point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 2.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 3.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 6.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);

  shearing_matrix = Shearing(0, 0, 0, 0, 0, 1);
  point5_result = shearing_matrix * point5;
  EXPECT_FLOAT_EQ(point5_result[0], 2.0f);
  EXPECT_FLOAT_EQ(point5_result[1], 3.0f);
  EXPECT_FLOAT_EQ(point5_result[2], 7.0f);
  EXPECT_FLOAT_EQ(point5_result[3], 1.0f);
};