#include "core/chapter5/chapter5.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include "gtest/gtest.h"

TEST(Chapter5Test, TestBasics) {
  Eigen::Vector4f origin = Point1Dim(1, 2, 3);
  Eigen::Vector4f direction = Vector1Dim(4, 5, 6);
  struct Ray ray(origin, direction);
  EXPECT_TRUE(origin == ray.origin);
  EXPECT_TRUE(direction == ray.direction);

  // Test of the position function
  origin = Point1Dim(2, 3, 4);
  direction = Vector1Dim(1, 0, 0);
  struct Ray ray2(origin, direction);
  Eigen::Vector4f result = Position(ray2, 0);
  EXPECT_EQ(result[0], 2.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = Position(ray2, 1);
  EXPECT_EQ(result[0], 3.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = Position(ray2, -1);
  EXPECT_EQ(result[0], 1.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = Position(ray2, 2.5);
  EXPECT_EQ(result[0], 4.5f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);
};

TEST(Chapter5Test, TestIntersection) {
  //
  Eigen::Vector4f origin = Point1Dim(0, 0, -5);
  Eigen::Vector4f direction = Vector1Dim(0, 0, 1);
  struct Ray ray(origin, direction);

  struct Sphere sphere;
  std::vector<float> intersections = Intersect(ray, sphere);
}