#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/camera.h"
#include "core/models/ray.h"
#include "core/models/world.h"
#include "core/ops/transformations.h"
#include "core/ops/vector_ops.h"
#include "core/ray_tracing_processor.h"
#include "core/visual/canvas.h"
#include "gtest/gtest.h"

TEST(Chapter7Test, TestWorld) {
  // TEST 1
  World world;
  // TEST 2
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  ray.IntersectWorld(world);
  std::vector<struct Intersection*>& intersections = ray.GetIntersections();
  EXPECT_EQ(intersections.size(), 4);
  EXPECT_EQ(intersections[0]->GetT(), 4.0f);  // 4.5f
  EXPECT_EQ(intersections[1]->GetT(), 4.5f);  // 5.5f
  EXPECT_EQ(intersections[2]->GetT(), 5.5f);  // 4.0f
  EXPECT_EQ(intersections[3]->GetT(), 6.0f);  // 6.0f

  // Test 2
  Object sphere_object(object_type::ObjectType::SPHERE);
  struct Intersection i(4, &sphere_object);
  struct Comps comps = ray.PrepareComputations(i);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, -1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == false);

  // Test 3
  Ray ray2(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct Intersection i2(1, &sphere_object);
  comps = ray2.PrepareComputations(i2);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, 1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == true);

  // TEST 4
  Ray ray3(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  struct Intersection i3(4, &(world.GetObjects()[1]));
  comps = ray3.PrepareComputations(i3);
  Eigen::Vector3f c = ray3.ShadeHit(world, comps);
  EXPECT_NEAR(c(0), 0.38066, 0.00001);
  EXPECT_NEAR(c(1), 0.47583, 0.00001);
  EXPECT_NEAR(c(2), 0.2855, 0.0001);

  // Test 5
  Ray ray4(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct PointLight point_light(RGBColor(1, 1, 1), Point1Dim(0, 0.25, 0));
  world.SetLight(point_light, 0);
  struct Intersection i4(0.5, &(world.GetObjects()[0]));
  comps = ray4.PrepareComputations(i4);
  c = ray4.ShadeHit(world, comps);
  EXPECT_NEAR(c(0), 0.90498, 0.00001);
  EXPECT_NEAR(c(1), 0.90498, 0.00001);
  EXPECT_NEAR(c(2), 0.90498, 0.00001);
};

TEST(Chapter7Test, TestWorld2) {
  // @TEST1
  World world;
  Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 1, 0));
  Eigen::Vector3f color = ray.ColorAt(world);
  EXPECT_NEAR(color(0), 0.0f, 0.00001);
  EXPECT_NEAR(color(1), 0.0f, 0.00001);
  EXPECT_NEAR(color(2), 0.0f, 0.00001);

  // @TEST2
  Ray ray2(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  color = ray2.ColorAt(world);
  EXPECT_NEAR(color(0), 0.38066f, 0.00001);
  EXPECT_NEAR(color(1), 0.47583f, 0.00001);
  EXPECT_NEAR(color(2), 0.2855f, 0.00001);

  // @TEST3
  world.GetObjects()[0].GetMaterial().ambient = 1;
  world.GetObjects()[1].GetMaterial().ambient = 1;
  Ray ray3(Point1Dim(0, 0, 0.75), Vector1Dim(0, 0, -1));
  color = ray3.ColorAt(world);
  Eigen::Vector3f inner_sphere_color =
      world.GetObjects()[0].GetMaterial().rgb_color;
  EXPECT_NEAR(color(0), inner_sphere_color(0), 0.00001);
  EXPECT_NEAR(color(1), inner_sphere_color(1), 0.00001);
  EXPECT_NEAR(color(2), inner_sphere_color(2), 0.00001);
};

TEST(Chapter7upTest, TestWorld3) {
  //
  Eigen::Matrix4f t = ViewTransformation(
      Point1Dim(0, 0, 0), Point1Dim(0, 0, -1), Vector1Dim(0, 1, 0));
  EXPECT_TRUE(t == Eigen::Matrix4f::Identity());

  //
  t = ViewTransformation(Point1Dim(0, 0, 0), Point1Dim(0, 0, 1),
                         Vector1Dim(0, 1, 0));
  EXPECT_TRUE(t == Scaling(-1, 1, -1));

  Eigen::Vector4f vec1 = Vector1Dim(1, 2, 3);
  Eigen::Vector4f vec2 = Vector1Dim(2, 3, 4);
  Eigen::Vector4f cross_result = CrossProduct4f(vec1, vec2);
  EXPECT_FLOAT_EQ(cross_result(0), -1.0f);
  EXPECT_FLOAT_EQ(cross_result(1), 2.0f);
  EXPECT_FLOAT_EQ(cross_result(2), -1.0f);
  EXPECT_FLOAT_EQ(cross_result(3), 0.0f);
  cross_result = CrossProduct4f(vec2, vec1);
  EXPECT_FLOAT_EQ(cross_result(0), 1.0f);
  EXPECT_FLOAT_EQ(cross_result(1), -2.0f);
  EXPECT_FLOAT_EQ(cross_result(2), 1.0f);
  EXPECT_FLOAT_EQ(cross_result(3), 0.0f);
  //
  t = ViewTransformation(Point1Dim(0, 0, 8), Point1Dim(0, 0, 0),
                         Vector1Dim(0, 1, 0));
  EXPECT_TRUE(t == Translation(0, 0, -8));

  //
  t = ViewTransformation(Point1Dim(1, 3, 2), Point1Dim(4, -2, 8),
                         Vector1Dim(1, 1, 0));
  EXPECT_NEAR(t(0, 0), -0.50709, 0.00001);
  EXPECT_NEAR(t(0, 1), 0.50709, 0.00001);
  EXPECT_NEAR(t(0, 2), 0.67612, 0.00001);
  EXPECT_NEAR(t(0, 3), -2.36643, 0.00001);
  EXPECT_NEAR(t(1, 0), 0.76772, 0.00001);
  EXPECT_NEAR(t(1, 1), 0.60609, 0.00001);
  EXPECT_NEAR(t(1, 2), 0.12122, 0.00001);
  EXPECT_NEAR(t(1, 3), -2.82843, 0.00001);
  EXPECT_NEAR(t(2, 0), -0.35857, 0.00001);
  EXPECT_NEAR(t(2, 1), 0.59761, 0.00001);
  EXPECT_NEAR(t(2, 2), -0.71714, 0.00001);
  EXPECT_NEAR(t(2, 3), 0.0f, 0.00001);
  EXPECT_NEAR(t(3, 0), 0.0f, 0.00001);
  EXPECT_NEAR(t(3, 1), 0.0f, 0.00001);
  EXPECT_NEAR(t(3, 2), 0.0f, 0.00001);
  EXPECT_NEAR(t(3, 3), 1.0f, 0.00001);
};

TEST(Chapter7Test, ImplementingACameraTest) {
  // Test 1
  Camera camera(160, 120, M_PI / 2.0);
  EXPECT_EQ(camera.h_size_, 160);
  EXPECT_EQ(camera.v_size_, 120);
  EXPECT_FLOAT_EQ(camera.field_of_view_, M_PI / 2.0);
  EXPECT_TRUE(camera.GetTransform() == Eigen::Matrix4f::Identity());

  // Test 2
  Camera camera2(200, 125, M_PI / 2.0);
  EXPECT_NEAR(camera2.pixel_size_, 0.01, 0.00001);

  // Test 3
  Camera camera3(125, 200, M_PI / 2);
  EXPECT_NEAR(camera3.pixel_size_, 0.01, 0.00001);

  // Test 4
  Camera camera4(201, 101, M_PI / 2.0);
  Ray ray;
  camera4.RayToPixel(100, 50, &ray);
  EXPECT_TRUE(ray.GetOrigin() == Point1Dim(0, 0, 0));
  EXPECT_NEAR(ray.GetDirection()[0], 0.0f, 0.00001f);
  EXPECT_NEAR(ray.GetDirection()[1], 0.0f, 0.00001f);
  EXPECT_NEAR(ray.GetDirection()[2], -1.0f, 0.00001f);

  // Test 5
  Ray ray2;
  camera4.RayToPixel(0, 0, &ray2);
  EXPECT_TRUE(ray2.GetOrigin() == Point1Dim(0, 0, 0));
  EXPECT_NEAR(ray2.GetDirection()[0], 0.66519f, 0.00001);
  EXPECT_NEAR(ray2.GetDirection()[1], 0.33259f, 0.00001);
  EXPECT_NEAR(ray2.GetDirection()[2], -0.66851f, 0.00001);

  // Test 6
  camera4.SetTransform(RotationY(M_PI / 4) * Translation(0, -2, 5));
  Ray ray3;
  camera4.RayToPixel(100, 50, &ray3);
  EXPECT_NEAR(ray3.GetOrigin()[0], 0, 0.0000001);
  EXPECT_NEAR(ray3.GetOrigin()[1], 2, 0.0000001);
  EXPECT_NEAR(ray3.GetOrigin()[2], -5, 0.000001);
  EXPECT_NEAR(ray3.GetDirection()[0], sqrt(2) / 2.0, 0.00001);
  EXPECT_NEAR(ray3.GetDirection()[1], 0.0f, 0.00001);
  EXPECT_NEAR(ray3.GetDirection()[2], -sqrt(2) / 2.0, 0.00001);
};

TEST(Chapter7Test, RenderFunctionTest) {
  // Test Rendering image
  World world;
  Camera camera(11, 11, M_PI / 2.0);
  camera.SetTransform(ViewTransformation(
      Point1Dim(0, 0, -5), Point1Dim(0, 0, 0), Vector1Dim(0, 1, 0)));
  Canvas image(11, 11);
  Render(camera, world, &image);
  EXPECT_NEAR(image.GetPixel(5, 5)[0], 0.38066, 0.00001);
  EXPECT_NEAR(image.GetPixel(5, 5)[1], 0.47583, 0.00001);
  EXPECT_NEAR(image.GetPixel(5, 5)[2], 0.2855, 0.00001);
};