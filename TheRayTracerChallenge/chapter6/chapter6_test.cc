#include "TheRayTracerChallenge/chapter6/chapter6.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include "TheRayTracerChallenge/chapter5/chapter5.h"
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
  struct Sphere sphere;
  Eigen::Matrix4f translation_matrix = Translation(0, 1, 0);
  sphere.transform = translation_matrix;
  Eigen::Vector4f point1 = Point1Dim(0, 1.70711, -0.70711);
  Eigen::Vector4f normal = NormalAtWorldPoint(sphere, point1);
  EXPECT_NEAR(normal[0], 0.0f, 0.00001);
  EXPECT_NEAR(normal[1], 0.70711f, 0.00001);
  EXPECT_NEAR(normal[2], -0.70711f, 0.00001);
  EXPECT_NEAR(normal[3], 0.0f, 0.00001);

  // Test 2 to transform Normals
  struct Sphere sphere2;
  Eigen::Matrix4f m = Scaling(1, 0.5, 1) * RotationZ((float)(M_PI / 5.0));
  sphere2.transform = m;
  Eigen::Vector4f point2 = Point1Dim(0, sqrt(2) / 2.0, -sqrt(2) / 2.0);
  Eigen::Vector4f normal2 = NormalAtWorldPoint(sphere2, point2);
  EXPECT_NEAR(normal2[0], 0.0f, 0.00001);
  EXPECT_NEAR(normal2[1], 0.97014f, 0.00001);
  EXPECT_NEAR(normal2[2], -0.24254f, 0.00001);
  EXPECT_NEAR(normal2[3], 0.0f, 0.00001);
};

TEST(Chapter6Test, ReflectingVectorsTest) {
  // @
  Eigen::Vector4f v = Vector1Dim(1, -1, 0);
  Eigen::Vector4f n = Vector1Dim(0, 1, 0);
  Eigen::Vector4f r = Reflect(v, n);
  EXPECT_EQ(r[0], 1.0f);
  EXPECT_EQ(r[1], 1.0f);
  EXPECT_EQ(r[2], 0.0f);
  // @
  v = Vector1Dim(0, -1, 0);
  n = Vector1Dim(sqrt(2) / 2, sqrt(2) / 2, 0);
  r = Reflect(v, n);
  EXPECT_NEAR(r[0], 1.0f, 0.00001);
  EXPECT_NEAR(r[1], 0.0f, 0.00001);
  EXPECT_NEAR(r[2], 0.0f, 0.00001);
};

TEST(Chapter6Test, PhongReflectionTest) {
  // Test material property in Sphere
  struct Sphere sphere;
  EXPECT_EQ(sphere.material.ambient, 0.1f);

  struct Material material;
  Eigen::Vector4f position = Point1Dim(0, 0, 0);

  // Test 1
  Eigen::Vector4f eyev = Vector1Dim(0, 0, -1);
  Eigen::Vector4f normalv = Vector1Dim(0, 0, -1);
  struct PointLight point_light(Color(1, 1, 1), Point1Dim(0, 0, -10));
  Eigen::Vector3f result =
      Lighting(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.9f, 0.0001);
  EXPECT_NEAR(result(1), 1.9f, 0.0001);
  EXPECT_NEAR(result(2), 1.9f, 0.0001);
  // Test 2
  eyev = Vector1Dim(0, sqrt(2) / 2.0, sqrt(2) / 2.0);
  normalv = Vector1Dim(0, 0, -1);
  result = Lighting(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.0f, 0.0001);
  EXPECT_NEAR(result(1), 1.0f, 0.0001);
  EXPECT_NEAR(result(2), 1.0f, 0.0001);
  // Test 3
  eyev = Vector1Dim(0, 0, -1);
  normalv = Vector1Dim(0, 0, -1);
  point_light.point = Point1Dim(0, 10, -10);
  result = Lighting(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 0.7364f, 0.0001);
  EXPECT_NEAR(result(1), 0.7364f, 0.0001);
  EXPECT_NEAR(result(2), 0.7364f, 0.0001);
  // Test 4
  eyev = Vector1Dim(0, -sqrt(2) / 2, -sqrt(2) / 2);
  normalv = Vector1Dim(0, 0, -1);
  result = Lighting(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.6364f, 0.0001f);
  EXPECT_NEAR(result(1), 1.6364f, 0.0001f);
  EXPECT_NEAR(result(2), 1.6364f, 0.0001f);
  // Test 5
  eyev = Vector1Dim(0, 0, -1);
  normalv = Vector1Dim(0, 0, -1);
  point_light.point = Point1Dim(0, 0, 10);
  result = Lighting(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 0.1f, 0.0001f);
  EXPECT_NEAR(result(1), 0.1f, 0.0001f);
  EXPECT_NEAR(result(2), 0.1f, 0.0001f);
};