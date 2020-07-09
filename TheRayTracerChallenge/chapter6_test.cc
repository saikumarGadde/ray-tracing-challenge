#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/object.h"
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/transformations.h"
#include "gtest/gtest.h"

TEST(Chapter6Test, NormalsOnSphere) {
  // Testing normals Test 1

  Object sphere_object(object_type::ObjectType::SPHERE);
  Eigen::Vector4f normal_vector = sphere_object.NormalAt(Point1Dim(1, 0, 0));
  EXPECT_EQ(normal_vector[0], 1.0f);
  EXPECT_EQ(normal_vector[1], 0.0f);
  EXPECT_EQ(normal_vector[2], 0.0f);
  EXPECT_EQ(normal_vector[3], 0.0f);

  // Test 2
  normal_vector = sphere_object.NormalAt(Point1Dim(0, 1, 0));
  EXPECT_EQ(normal_vector[0], 0.0f);
  EXPECT_EQ(normal_vector[1], 1.0f);
  EXPECT_EQ(normal_vector[2], 0.0f);
  EXPECT_EQ(normal_vector[3], 0.0f);
  // Test 3
  normal_vector = sphere_object.NormalAt(Point1Dim(0, 0, 1));
  EXPECT_EQ(normal_vector[0], 0.0f);
  EXPECT_EQ(normal_vector[1], 0.0f);
  EXPECT_EQ(normal_vector[2], 1.0f);
  EXPECT_EQ(normal_vector[3], 0.0f);
  // Test 4
  normal_vector = sphere_object.NormalAt(
      Point1Dim(sqrt(3) / 3.0, sqrt(3) / 3.0, sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector[0], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector[1], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector[2], (float)(sqrt(3) / 3.0));
  EXPECT_FLOAT_EQ(normal_vector[3], 0.0f);
};

TEST(Chapter6Test, TransformingNormalsTest) {
  // Test 1 to transform normals
  Object sphere(object_type::ObjectType::SPHERE);
  sphere.SetTransform(Translation(0, 1, 0));
  Eigen::Vector4f normal =
      sphere.NormalAtWorldPoint(Point1Dim(0, 1.70711, -0.70711));
  EXPECT_NEAR(normal[0], 0.0f, 0.00001);
  EXPECT_NEAR(normal[1], 0.70711f, 0.00001);
  EXPECT_NEAR(normal[2], -0.70711f, 0.00001);
  EXPECT_NEAR(normal[3], 0.0f, 0.00001);

  // Test 2 to transform Normals
  sphere.SetTransform(Scaling(1, 0.5, 1) * RotationZ((float)(M_PI / 5.0)));
  normal =
      sphere.NormalAtWorldPoint(Point1Dim(0, sqrt(2) / 2.0, -sqrt(2) / 2.0));
  EXPECT_NEAR(normal[0], 0.0f, 0.00001);
  EXPECT_NEAR(normal[1], 0.97014f, 0.00001);
  EXPECT_NEAR(normal[2], -0.24254f, 0.00001);
  EXPECT_NEAR(normal[3], 0.0f, 0.00001);
};

TEST(Chapter6Test, ReflectingVectorsTest) {
  // @
  Eigen::Vector4f v = Vector1Dim(1, -1, 0);
  Eigen::Vector4f n = Vector1Dim(0, 1, 0);
  Eigen::Vector4f r = Ray::Reflect(v, n);
  EXPECT_EQ(r[0], 1.0f);
  EXPECT_EQ(r[1], 1.0f);
  EXPECT_EQ(r[2], 0.0f);
  // @
  v = Vector1Dim(0, -1, 0);
  n = Vector1Dim(sqrt(2) / 2, sqrt(2) / 2, 0);
  r = Ray::Reflect(v, n);
  EXPECT_NEAR(r[0], 1.0f, 0.00001);
  EXPECT_NEAR(r[1], 0.0f, 0.00001);
  EXPECT_NEAR(r[2], 0.0f, 0.00001);
};

TEST(Chapter6Test, PhongReflectionTest) {
  // Test material property in Sphere
  Object sphere(object_type::ObjectType::SPHERE);

  EXPECT_EQ(sphere.GetMaterial().ambient, 0.1f);

  struct Material material;
  Eigen::Vector4f position = Point1Dim(0, 0, 0);

  // Test 1
  Eigen::Vector4f eyev = Vector1Dim(0, 0, -1);
  Eigen::Vector4f normalv = Vector1Dim(0, 0, -1);
  struct PointLight point_light(RGBColor(1, 1, 1), Point1Dim(0, 0, -10));
  Eigen::Vector3f result =
      Ray::Lighting2(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.9f, 0.0001);
  EXPECT_NEAR(result(1), 1.9f, 0.0001);
  EXPECT_NEAR(result(2), 1.9f, 0.0001);

  // Test 2
  eyev = Vector1Dim(0, sqrt(2) / 2.0, sqrt(2) / 2.0);
  normalv = Vector1Dim(0, 0, -1);
  result = Ray::Lighting2(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.0f, 0.0001);
  EXPECT_NEAR(result(1), 1.0f, 0.0001);
  EXPECT_NEAR(result(2), 1.0f, 0.0001);

  // Test 3
  eyev = Vector1Dim(0, 0, -1);
  normalv = Vector1Dim(0, 0, -1);
  point_light.SetLightPosition(Point1Dim(0, 10, -10));
  result = Ray::Lighting2(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 0.7364f, 0.0001);
  EXPECT_NEAR(result(1), 0.7364f, 0.0001);
  EXPECT_NEAR(result(2), 0.7364f, 0.0001);

  // Test 4
  eyev = Vector1Dim(0, -sqrt(2) / 2, -sqrt(2) / 2);
  normalv = Vector1Dim(0, 0, -1);
  result = Ray::Lighting2(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 1.6364f, 0.0001f);
  EXPECT_NEAR(result(1), 1.6364f, 0.0001f);
  EXPECT_NEAR(result(2), 1.6364f, 0.0001f);

  // Test 5
  eyev = Vector1Dim(0, 0, -1);
  normalv = Vector1Dim(0, 0, -1);
  point_light.SetLightPosition(Point1Dim(0, 0, 10));
  result = Ray::Lighting2(material, point_light, position, eyev, normalv);
  EXPECT_NEAR(result(0), 0.1f, 0.0001f);
  EXPECT_NEAR(result(1), 0.1f, 0.0001f);
  EXPECT_NEAR(result(2), 0.1f, 0.0001f);
};