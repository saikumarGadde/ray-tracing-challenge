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
  std::vector<struct Intersection*> intersections = Intersect(ray, sphere);
  EXPECT_EQ((intersections[0])->t, 4.0f);
  EXPECT_EQ(intersections[1]->t, 6.0f);

  // Test case for an intersection tangentially
  origin = Point1Dim(0, 1, -5);
  struct Ray ray2(origin, direction);
  intersections = Intersect(ray2, sphere);
  EXPECT_EQ(intersections[0]->t, 5.0f);
  EXPECT_EQ(intersections[1]->t, 5.0f);

  // Test case for no Intersections
  origin = Point1Dim(0, 2, -5);
  struct Ray ray3(origin, direction);
  intersections = Intersect(ray3, sphere);
  EXPECT_EQ(intersections.size(), 0);

  // Ray starting at the center of the sphere
  origin = Point1Dim(0, 0, 0);
  struct Ray ray4(origin, direction);
  intersections = Intersect(ray4, sphere);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0]->t, -1.0f);
  EXPECT_EQ(intersections[1]->t, 1.0f);

  // Sphere is behind the ray
  origin = Point1Dim(0, 0, 5);
  struct Ray ray5(origin, direction);
  intersections = Intersect(ray5, sphere);
  EXPECT_EQ(intersections.size(), 2);
  EXPECT_EQ(intersections[0]->t, -6.0f);
  EXPECT_EQ(intersections[1]->t, -4.0f);
};

TEST(Chapter5Test, TestTrackingIntersections) {
  // Tests tracking intersections
  struct Sphere sphere;
  // Create a data structure of an Intersection
  struct Intersection intersection(3.5, sphere);
  // Assertions
  EXPECT_EQ(intersection.t, 3.5f);
  EXPECT_EQ(intersection.sphere.center, sphere.center);
  EXPECT_EQ(intersection.sphere.radius, sphere.radius);

  // Test 1
  struct Intersection i1(1, sphere);
  struct Intersection i2(1, sphere);
  struct Intersection* intersections[2] = {&i1, &i2};
  struct Intersection* result = Hit(intersections, 2);
  EXPECT_EQ(result, &i1);

  // Test 2
  struct Intersection i3(-1, sphere);
  struct Intersection i4(1, sphere);
  struct Intersection* intersections2[2] = {&i3, &i4};
  struct Intersection* result2 = Hit(intersections2, 2);
  EXPECT_EQ(result2, &i4);

  // Test 4
  struct Intersection i5(-2, sphere);
  struct Intersection i6(-1, sphere);
  struct Intersection* intersections3[2] = {&i5, &i6};
  struct Intersection* result3 = Hit(intersections3, 2);
  EXPECT_EQ(result3, nullptr);

  // Test 5
  struct Intersection i7(5, sphere);
  struct Intersection i8(7, sphere);
  struct Intersection i9(-3, sphere);
  struct Intersection i10(2, sphere);
  struct Intersection* intersections4[4] = {&i7, &i8, &i9, &i10};
  struct Intersection* result4 = Hit(intersections4, 4);
  EXPECT_EQ(result4, &i10);
};

TEST(Chapter5Test, TestTransformations) {
  // Test : Translating a ray
  Eigen::Vector4f origin = Point1Dim(1, 2, 3);
  Eigen::Vector4f direction = Vector1Dim(0, 1, 0);
  struct Ray ray(origin, direction);
  // Translation matrix
  Eigen::Matrix4f m = Translation(3, 4, 5);
  struct Ray transformed_ray = Transform(m, ray);
  EXPECT_EQ(transformed_ray.origin, Point1Dim(4, 6, 8));
  EXPECT_EQ(transformed_ray.direction, Vector1Dim(0, 1, 0));

  // Test: Scaling a ray
  Eigen::Matrix4f scaling_matrix = Scaling(2, 3, 4);
  struct Ray scaled_ray = Transform(scaling_matrix, ray);
  EXPECT_EQ(scaled_ray.origin, Point1Dim(2, 6, 12));
  EXPECT_EQ(scaled_ray.direction, Vector1Dim(0, 3, 0));
};

TEST(Chapter5Test, SphereTransformationsTest) {
  // Test :
  struct Sphere sphere;
  Eigen::Matrix4f identity_matrix = Eigen::Matrix4f::Identity();
  EXPECT_EQ(sphere.transform, identity_matrix);

  // Testing the transformation of the ray using sphere.transform

  Eigen::Vector4f origin = Point1Dim(0, 0, -5);
  Eigen::Vector4f direction = Vector1Dim(0, 0, 1);
  struct Ray ray(origin, direction);
  struct Sphere sphere2;
  sphere2.transform = Scaling(2, 2, 2);
  std::vector<struct Intersection*> intersections = Intersect(ray, sphere2);
  EXPECT_EQ(intersections[0]->t, 3);
  EXPECT_EQ(intersections[1]->t, 7);
}