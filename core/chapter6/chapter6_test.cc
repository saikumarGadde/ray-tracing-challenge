#include "core/chapter6/chapter6.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/chapter5/chapter5.h"
#include "gtest/gtest.h"

TEST(Chapter6Test, NormalsOnSphere) {
  // Testing normals Test 1
  struct Sphere sphere;
  Eigen::Vector4f point = Point1Dim(1, 0, 0);
  Eigen::Vector4f normal_vector = NormalAt(sphere, point);
  EXPECT_EQ(normal_vector[0], 1.0f);
  EXPECT_EQ(normal_vector[1], 0.0f);
  EXPECT_EQ(normal_vector[2], 0.0f);
  EXPECT_EQ(normal_vector[3], 0.0f);
  // Test 2
  Eigen::Vector4f point1 = Point1Dim(0, 1, 0);
  Eigen::Vector4f normal_vector1 = NormalAt(sphere, point1);
  EXPECT_EQ(normal_vector1[0], 0.0f);
  EXPECT_EQ(normal_vector1[1], 1.0f);
  EXPECT_EQ(normal_vector1[2], 0.0f);
  EXPECT_EQ(normal_vector1[3], 0.0f);
  // Test 3
  Eigen::Vector4f point2 = Point1Dim(0, 0, 1);
  Eigen::Vector4f normal_vector2 = NormalAt(sphere, point2);
  EXPECT_EQ(normal_vector2[0], 0.0f);
  EXPECT_EQ(normal_vector2[1], 0.0f);
  EXPECT_EQ(normal_vector2[2], 1.0f);
  EXPECT_EQ(normal_vector2[3], 0.0f);
  // Test 4
  Eigen::Vector4f point3 =
      Point1Dim(sqrt(3) / 3.0, sqrt(3) / 3.0, sqrt(3) / 3.0);
  Eigen::Vector4f normal_vector3 = NormalAt(sphere, point3);
  EXPECT_FLOAT_EQ(normal_vector3[0], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector3[1], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector3[2], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector3[3], 0.0f);
};

TEST(Chapter6Test, TransformingNormalsTest) {
  // Test 1 to transform normals
}