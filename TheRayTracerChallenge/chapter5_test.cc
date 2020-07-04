#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/transformations.h"
#include "gtest/gtest.h"

TEST(Chapter5Test, TestBasics) {
  Eigen::Vector4f origin = Point1Dim(1, 2, 3);
  Eigen::Vector4f direction = Vector1Dim(4, 5, 6);
  Ray ray(origin, direction);
  EXPECT_TRUE(origin == ray.GetOrigin());
  EXPECT_TRUE(direction == ray.GetDirection());

  // Test of the position function
  origin = Point1Dim(2, 3, 4);
  direction = Vector1Dim(1, 0, 0);
  Ray ray2(origin, direction);
  Eigen::Vector4f result = ray2.Position(0);
  EXPECT_EQ(result[0], 2.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = ray2.Position(1);
  EXPECT_EQ(result[0], 3.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = ray2.Position(-1);
  EXPECT_EQ(result[0], 1.0f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);

  result = ray2.Position(2.5);
  EXPECT_EQ(result[0], 4.5f);
  EXPECT_EQ(result[1], 3.0f);
  EXPECT_EQ(result[2], 4.0f);
  EXPECT_EQ(result[3], 1.0f);
};

TEST(Chapter5Test, TestIntersection) {
  //
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  struct Sphere sphere;
  struct Object sphere_object(sphere);
  ray.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections = ray.GetIntersections();
  EXPECT_EQ(intersections[0]->t_, 4.0f);
  EXPECT_EQ(intersections[1]->t_, 6.0f);

  // Test case for an intersection tangentially
  Ray ray2(Point1Dim(0, 1, -5), Vector1Dim(0, 0, 1));
  ray2.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections2 = ray2.GetIntersections();
  EXPECT_EQ(intersections2[0]->t_, 5.0f);
  EXPECT_EQ(intersections2[1]->t_, 5.0f);

  // Test case for no Intersections
  Ray ray3(Point1Dim(0, 2, -5), Vector1Dim(0, 0, 1));
  ray3.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections3 = ray3.GetIntersections();
  EXPECT_EQ(intersections3.size(), 0);

  // Ray starting at the center of the sphere
  Ray ray4(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  ray4.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections4 = ray4.GetIntersections();
  EXPECT_EQ(intersections4.size(), 2);
  EXPECT_EQ(intersections4[0]->t_, -1.0f);
  EXPECT_EQ(intersections4[1]->t_, 1.0f);

  // Sphere is behind the ray
  Ray ray5(Point1Dim(0, 0, 5), Vector1Dim(0, 0, 1));
  ray5.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections5 = ray5.GetIntersections();
  EXPECT_EQ(intersections5.size(), 2);
  EXPECT_EQ(intersections5[0]->t_, -6.0f);
  EXPECT_EQ(intersections5[1]->t_, -4.0f);
};

// TEST(Chapter5Test, TestTrackingIntersections) {
//   // Tests tracking intersections
//   struct Sphere sphere;
//   // Create a data structure of an Intersection
//   struct Intersection intersection(3.5, sphere);
//   // Assertions
//   EXPECT_EQ(intersection.t, 3.5f);
//   EXPECT_EQ(intersection.sphere.center, sphere.center);
//   EXPECT_EQ(intersection.sphere.radius, sphere.radius);

//   // Test 1
//   struct Intersection i1(1, sphere);
//   struct Intersection i2(1, sphere);
//   struct Intersection* intersections[2] = {&i1, &i2};
//   struct Intersection* result = Hit(intersections, 2);
//   EXPECT_EQ(result, &i1);

//   // Test 2
//   struct Intersection i3(-1, sphere);
//   struct Intersection i4(1, sphere);
//   struct Intersection* intersections2[2] = {&i3, &i4};
//   struct Intersection* result2 = Hit(intersections2, 2);
//   EXPECT_EQ(result2, &i4);

//   // Test 4
//   struct Intersection i5(-2, sphere);
//   struct Intersection i6(-1, sphere);
//   struct Intersection* intersections3[2] = {&i5, &i6};
//   struct Intersection* result3 = Hit(intersections3, 2);
//   EXPECT_EQ(result3, nullptr);

//   // Test 5
//   struct Intersection i7(5, sphere);
//   struct Intersection i8(7, sphere);
//   struct Intersection i9(-3, sphere);
//   struct Intersection i10(2, sphere);
//   struct Intersection* intersections4[4] = {&i7, &i8, &i9, &i10};
//   struct Intersection* result4 = Hit(intersections4, 4);
//   EXPECT_EQ(result4, &i10);
// };

TEST(Chapter5Test, TestTransformations) {
  // Test : Translating a ray
  Ray ray(Point1Dim(1, 2, 3), Vector1Dim(0, 1, 0));
  // Translation matrix
  ray.SetTransform(Translation(3, 4, 5));
  EXPECT_TRUE(ray.GetOrigin() == Point1Dim(4, 6, 8));
  EXPECT_TRUE(ray.GetDirection() == Vector1Dim(0, 1, 0));

  // Test: Scaling a ray
  Ray ray2(Point1Dim(1, 2, 3), Vector1Dim(0, 1, 0));
  ray2.SetTransform(Scaling(2, 3, 4));
  EXPECT_TRUE(ray2.GetOrigin() == Point1Dim(2, 6, 12));
  EXPECT_TRUE(ray2.GetDirection() == Vector1Dim(0, 3, 0));
};

TEST(Chapter5Test, SphereTransformationsTest) {
  // Test :
  struct Sphere sphere;
  Eigen::Matrix4f identity_matrix = Eigen::Matrix4f::Identity();
  EXPECT_EQ(sphere.GetTransform(), identity_matrix);

  // Testing the transformation of the ray using sphere.transform
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  sphere.SetTransform(Scaling(2, 2, 2));
  struct Object sphere_object(sphere);
  ray.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections = ray.GetIntersections();
  EXPECT_EQ(intersections[0]->t_, 3.0f);
  EXPECT_EQ(intersections[1]->t_, 7.0f);

  // Testing method 2
  ray.ClearIntersections();
  sphere.SetTransform(Translation(5, 0, 0));
  struct Object sphere_object2(sphere);
  ray.IntersectObject(sphere_object2);
  std::vector<struct Intersection*>& intersections2 = ray.GetIntersections();
  EXPECT_EQ(intersections2.size(), 0);
};