#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/object_type.h"
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/transformations.h"
#include "gtest/gtest.h"

TEST(Chapter5Test, TestBasics) {
  Ray ray(Point1Dim(1, 2, 3), Vector1Dim(4, 5, 6));
  EXPECT_TRUE(Point1Dim(1, 2, 3) == ray.GetOrigin());
  EXPECT_TRUE(Vector1Dim(4, 5, 6) == ray.GetDirection());

  // Test of the position function
  Ray ray2(Point1Dim(2, 3, 4), Vector1Dim(1, 0, 0));
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
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  Object sphere_object(object_type::ObjectType::SPHERE);
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

TEST(Chapter5Test, TestTrackingIntersections) {
  // Tests tracking intersections
  Object sphere_object(object_type::ObjectType::SPHERE);
  struct Intersection intersection(3.5, &sphere_object);
  // Assertions
  EXPECT_EQ(intersection.GetT(), 3.5f);
  EXPECT_EQ(intersection.GetObject()->GetSphere().GetCenter(),
            sphere_object.GetSphere().GetCenter());
  EXPECT_EQ(intersection.GetObject()->GetSphere().GetRadius(),
            sphere_object.GetSphere().GetRadius());

  // Test 1
  struct Intersection i1(1, &sphere_object);
  struct Intersection i2(1, &sphere_object);
  Ray ray1(Point1Dim(0, 0, 0), Vector1Dim(1, 1, 1));
  ray1.AddIntersection(&i1);
  ray1.AddIntersection(&i2);
  EXPECT_EQ(ray1.PopIntersection(), &i1);

  // Test 2
  struct Intersection i3(-1, &sphere_object);
  struct Intersection i4(1, &sphere_object);
  Ray ray2(Point1Dim(0, 0, 0), Vector1Dim(1, 1, 1));
  ray2.AddIntersection(&i3);
  ray2.AddIntersection(&i4);
  EXPECT_EQ(ray2.PopIntersection(), &i4);

  // Test 4
  struct Intersection i5(-2, &sphere_object);
  struct Intersection i6(-1, &sphere_object);
  Ray ray3(Point1Dim(0, 0, 0), Vector1Dim(1, 1, 1));
  ray3.AddIntersection(&i5);
  ray3.AddIntersection(&i6);
  EXPECT_EQ(ray3.PopIntersection(), nullptr);

  // Test 5
  struct Intersection i7(5, &sphere_object);
  struct Intersection i8(7, &sphere_object);
  struct Intersection i9(-3, &sphere_object);
  struct Intersection i10(2, &sphere_object);
  Ray ray4(Point1Dim(0, 0, 0), Vector1Dim(1, 1, 1));
  ray4.AddIntersection(&i7);
  ray4.AddIntersection(&i9);
  ray4.AddIntersection(&i8);
  ray4.AddIntersection(&i10);
  EXPECT_EQ(ray4.PopIntersection(), &i10);
};

TEST(Chapter5Test, TestTransformations) {
  // Test : Translating a ray
  Ray ray(Point1Dim(1, 2, 3), Vector1Dim(0, 1, 0));
  // Translation matrix
  Eigen::Matrix4f translation_matrix = Translation(3, 4, 5);
  ray.SetTransform(translation_matrix);
  EXPECT_TRUE(ray.GetOrigin() == Point1Dim(4, 6, 8));
  EXPECT_TRUE(ray.GetDirection() == Vector1Dim(0, 1, 0));

  // Test: Scaling a ray
  Ray ray2(Point1Dim(1, 2, 3), Vector1Dim(0, 1, 0));
  Eigen::Matrix4f scaling_matrix = Scaling(2, 3, 4);
  ray2.SetTransform(scaling_matrix);
  EXPECT_TRUE(ray2.GetOrigin() == Point1Dim(2, 6, 12));
  EXPECT_TRUE(ray2.GetDirection() == Vector1Dim(0, 3, 0));
};

TEST(Chapter5Test, SphereTransformationsTest) {
  Object sphere_object(object_type::ObjectType::SPHERE);
  Eigen::Matrix4f identity_matrix = Eigen::Matrix4f::Identity();
  EXPECT_EQ(sphere_object.GetTransform(), identity_matrix);

  // Testing the transformation of the ray using sphere.transform
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  Eigen::Matrix4f scaling_matrix = Scaling(2, 2, 2);
  sphere_object.SetTransform(scaling_matrix);
  ray.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections = ray.GetIntersections();
  EXPECT_EQ(intersections[0]->t_, 3.0f);
  EXPECT_EQ(intersections[1]->t_, 7.0f);

  // Testing method 2
  ray.ClearIntersections();
  Eigen::Matrix4f translation_matrix = Translation(5, 0, 0);
  sphere_object.SetTransform(translation_matrix);
  ray.IntersectObject(sphere_object);
  std::vector<struct Intersection*>& intersections2 = ray.GetIntersections();
  EXPECT_EQ(intersections2.size(), 0);
};