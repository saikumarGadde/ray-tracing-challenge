#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/camera.h"
#include "core/models/object_type.h"
#include "core/models/phong_model.h"
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/models/world.h"
#include "core/ops/color_ops.h"
#include "core/ops/transformations.h"
#include "core/ops/vector_ops.h"
#include "core/visual/canvas.h"
#include "gtest/gtest.h"

TEST(Chapter9Test, Chapter9Task1) {
  // Test 1
  Object sphere(object_type::ObjectType::SPHERE);
  EXPECT_TRUE(sphere.GetTransform() == Eigen::Matrix4f::Identity());

  // Test 2
  Object sphere2(object_type::ObjectType::SPHERE);
  sphere2.SetTransform(Translation(2, 3, 4));
  EXPECT_TRUE(sphere2.GetTransform() == Translation(2, 3, 4));

  // Test 3
  Object sphere3(object_type::ObjectType::SPHERE);

  // Test 4
  Object sphere4(object_type::ObjectType::SPHERE);
  struct Material& material = sphere4.GetMaterial();
  std::cout << "Material ambient is : " << material.ambient << std::endl;
  EXPECT_TRUE(material.ambient == 0.1f);
};

TEST(Chapter9Test, Chapter9Task2) {
  // Test 1
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  Object sphere(object_type::ObjectType::SPHERE);
  sphere.SetTransform(Scaling(2, 2, 2));
  ray.IntersectObject(sphere);
  EXPECT_TRUE(ray.saved_origin_ == Point1Dim(0, 0, -2.5));
  EXPECT_TRUE(ray.saved_direction_ == Vector1Dim(0, 0, 0.5));
  // Test 2
  Ray ray2(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  sphere.SetTransform(Translation(5, 0, 0));
  ray2.IntersectObject(sphere);
  EXPECT_TRUE(ray2.saved_origin_ == Point1Dim(-5, 0, -5));
  EXPECT_TRUE(ray2.saved_direction_ == Vector1Dim(0, 0, 1));
  // Test 3
  Object sphere3(object_type::ObjectType::SPHERE);
  sphere3.SetTransform(Translation(0, 1, 0));
  Eigen::Vector4f n3 =
      sphere3.NormalAtWorldPoint(Point1Dim(0, 1.70711, -0.70711));
  EXPECT_NEAR(n3(0), 0.0f, 0.0001);
  EXPECT_NEAR(n3(1), 0.70711, 0.0001);
  EXPECT_NEAR(n3(2), -0.70711, 0.0001);
  // Test 4
  Object sphere4(object_type::ObjectType::SPHERE);
  sphere4.SetTransform(Scaling(1, 0.5, 1) * RotationZ(M_PI / 5.0));
  Eigen::Vector4f n4 = sphere4.NormalAtWorldPoint(
      Point1Dim(0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0));
  EXPECT_NEAR(n4(0), 0.0f, 0.0001);
  EXPECT_NEAR(n4(1), 0.97014, 0.0001);
  EXPECT_NEAR(n4(2), -0.24254, 0.0001);
};

TEST(Chapter9Test, PlaneTest) {
  // // Testing the plane
  Object plane(object_type::ObjectType::PLANE);
  Eigen::Vector4f n1 = plane.NormalAtLocalPoint(Point1Dim(0, 0, 0));
  Eigen::Vector4f n2 = plane.NormalAtLocalPoint(Point1Dim(10, 0, -10));
  Eigen::Vector4f n3 = plane.NormalAtLocalPoint(Point1Dim(-5, 0, 150));
  EXPECT_TRUE(n1 == Vector1Dim(0, 1, 0));
  EXPECT_TRUE(n2 == Vector1Dim(0, 1, 0));
  EXPECT_TRUE(n3 == Vector1Dim(0, 1, 0));

  // Test 2
  Ray ray(Point1Dim(0, 10, 0), Vector1Dim(0, 0, 1));
  ray.LocalIntersectPlane(plane, ray.GetOrigin(), ray.GetDirection());
  EXPECT_TRUE(ray.PopIntersection() == nullptr);

  // Test 3
  Ray ray2(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  ray2.LocalIntersectPlane(plane, ray2.GetOrigin(), ray2.GetDirection());
  EXPECT_TRUE(ray2.PopIntersection() == nullptr);

  // Test 4
  Ray ray3(Point1Dim(0, 1, 0), Vector1Dim(0, -1, 0));
  ray3.LocalIntersectPlane(plane, ray3.GetOrigin(), ray3.GetDirection());
  struct Intersection* hit = ray3.PopIntersection();
  EXPECT_TRUE(ray3.GetIntersections().size() == 1);
  EXPECT_TRUE(hit->GetT() == 1);
  EXPECT_TRUE(hit->GetObject() == &plane);

  // Test 5
  Ray ray4(Point1Dim(0, -1, 0), Vector1Dim(0, 1, 0));
  ray4.LocalIntersectPlane(plane, ray4.GetOrigin(), ray4.GetDirection());
  hit = ray4.PopIntersection();
  EXPECT_TRUE(ray4.GetIntersections().size() == 1);
  EXPECT_TRUE(hit->GetT() == 1);
  EXPECT_TRUE(hit->GetObject() == &plane);
};