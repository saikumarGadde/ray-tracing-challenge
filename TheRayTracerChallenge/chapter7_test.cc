#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/ray.h"
#include "core/models/world.h"
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
  Sphere shape;
  struct Intersection i(4, Object(shape));
  struct Comps comps = ray.PrepareComputations(i);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, -1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == false);

  // Test 3
  Ray ray2(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct Intersection i2(1, Object(shape));
  comps = ray2.PrepareComputations(i2);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, 1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == true);

  // TEST 4
  Ray ray3(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  struct Intersection i3(4, Object(world.GetObjects()[1]));
  comps = ray3.PrepareComputations(i3);
  Eigen::Vector3f c = ray3.ShadeHit(world, comps);
  EXPECT_NEAR(c(0), 0.38066, 0.00001);
  EXPECT_NEAR(c(1), 0.47583, 0.00001);
  EXPECT_NEAR(c(2), 0.2855, 0.0001);

  // Test 5
  Ray ray4(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct PointLight point_light(RGBColor(1, 1, 1), Point1Dim(0, 0.25, 0));
  world.SetLight(point_light, 0);
  struct Intersection i4(0.5, Object(world.GetObjects()[0]));
  comps = ray4.PrepareComputations(i4);
  c = ray4.ShadeHit(world, comps);
  EXPECT_NEAR(c(0), 0.90498, 0.00001);
  EXPECT_NEAR(c(1), 0.90498, 0.00001);
  EXPECT_NEAR(c(2), 0.90498, 0.00001);
};

// TEST(Chapter7Test, TestWorld2) {
//   // @TEST1
//   World world;
//   struct Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 1, 0));
//   Eigen::Vector3f color = ColorAt(world, ray);
//   EXPECT_NEAR(color(0), 0.0f, 0.00001);
//   EXPECT_NEAR(color(1), 0.0f, 0.00001);
//   EXPECT_NEAR(color(2), 0.0f, 0.00001);

//   // @TEST2
//   struct Ray ray2(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
//   color = ColorAt(world, ray2);
//   EXPECT_NEAR(color(0), 0.38066f, 0.00001);
//   EXPECT_NEAR(color(1), 0.47583f, 0.00001);
//   EXPECT_NEAR(color(2), 0.2855f, 0.00001);

//   // @TEST3
//   world.objects[0].sphere.material.ambient = 1;
//   world.objects[1].sphere.material.ambient = 1;
//   struct Ray ray3(Point1Dim(0, 0, 0.75), Vector1Dim(0, 0, -1));
//   color = ColorAt(world, ray3);
//   Eigen::Vector3f inner_sphere_color =
//       world.objects[0].sphere.material.rgb_color;
//   EXPECT_NEAR(color(0), inner_sphere_color(0), 0.00001);
//   EXPECT_NEAR(color(1), inner_sphere_color(1), 0.00001);
//   EXPECT_NEAR(color(2), inner_sphere_color(2), 0.00001);
// };

// TEST(Chapter7upTest, TestWorld3) {
//   //
//   Eigen::Matrix4f t = ViewTransformation(
//       Point1Dim(0, 0, 0), Point1Dim(0, 0, -1), Vector1Dim(0, 1, 0));
//   EXPECT_TRUE(t == Eigen::Matrix4f::Identity());

//   //
//   t = ViewTransformation(Point1Dim(0, 0, 0), Point1Dim(0, 0, 1),
//                          Vector1Dim(0, 1, 0));
//   EXPECT_TRUE(t == Scaling(-1, 1, -1));

//   Eigen::Vector4f vec1 = Vector1Dim(1, 2, 3);
//   Eigen::Vector4f vec2 = Vector1Dim(2, 3, 4);
//   Eigen::Vector4f cross_result = CrossProduct4f(vec1, vec2);
//   EXPECT_FLOAT_EQ(cross_result(0), -1.0f);
//   EXPECT_FLOAT_EQ(cross_result(1), 2.0f);
//   EXPECT_FLOAT_EQ(cross_result(2), -1.0f);
//   EXPECT_FLOAT_EQ(cross_result(3), 0.0f);
//   cross_result = CrossProduct4f(vec2, vec1);
//   EXPECT_FLOAT_EQ(cross_result(0), 1.0f);
//   EXPECT_FLOAT_EQ(cross_result(1), -2.0f);
//   EXPECT_FLOAT_EQ(cross_result(2), 1.0f);
//   EXPECT_FLOAT_EQ(cross_result(3), 0.0f);
//   //
//   t = ViewTransformation(Point1Dim(0, 0, 8), Point1Dim(0, 0, 0),
//                          Vector1Dim(0, 1, 0));
//   std::cout << "translation is " << t << std::endl;
//   std::cout << "translation is " << Translation(0, 0, -8) << std::endl;
//   EXPECT_TRUE(t == Translation(0, 0, -8));

//   //
//   t = ViewTransformation(Point1Dim(1, 3, 2), Point1Dim(4, -2, 8),
//                          Vector1Dim(1, 1, 0));
//   EXPECT_NEAR(t(0, 0), -0.50709, 0.00001);
//   EXPECT_NEAR(t(0, 1), 0.50709, 0.00001);
//   EXPECT_NEAR(t(0, 2), 0.67612, 0.00001);
//   EXPECT_NEAR(t(0, 3), -2.36643, 0.00001);
//   EXPECT_NEAR(t(1, 0), 0.76772, 0.00001);
//   EXPECT_NEAR(t(1, 1), 0.60609, 0.00001);
//   EXPECT_NEAR(t(1, 2), 0.12122, 0.00001);
//   EXPECT_NEAR(t(1, 3), -2.82843, 0.00001);
//   EXPECT_NEAR(t(2, 0), -0.35857, 0.00001);
//   EXPECT_NEAR(t(2, 1), 0.59761, 0.00001);
//   EXPECT_NEAR(t(2, 2), -0.71714, 0.00001);
//   EXPECT_NEAR(t(2, 3), 0.0f, 0.00001);
//   EXPECT_NEAR(t(3, 0), 0.0f, 0.00001);
//   EXPECT_NEAR(t(3, 1), 0.0f, 0.00001);
//   EXPECT_NEAR(t(3, 2), 0.0f, 0.00001);
//   EXPECT_NEAR(t(3, 3), 1.0f, 0.00001);
// };

// TEST(Chapter7Test, ImplementingACameraTest) {
//   // Test 1
//   struct Camera camera(160, 120, M_PI / 2.0);
//   EXPECT_EQ(camera.h_size, 160);
//   EXPECT_EQ(camera.v_size, 120);
//   EXPECT_FLOAT_EQ(camera.field_of_view, M_PI / 2.0);
//   EXPECT_TRUE(camera.transform == Eigen::Matrix4f::Identity());

//   // Test 2
//   struct Camera camera2(200, 125, M_PI / 2.0);
//   EXPECT_NEAR(camera2.pixel_size, 0.01, 0.00001);

//   // Test 3
//   struct Camera camera3(125, 200, M_PI / 2);
//   EXPECT_NEAR(camera3.pixel_size, 0.01, 0.00001);

//   // Test 4
//   struct Camera camera4(201, 101, M_PI / 2.0);
//   struct Ray ray = RayToPixel(camera4, 100, 50);
//   EXPECT_TRUE(ray.origin == Point1Dim(0, 0, 0));
//   EXPECT_NEAR(ray.direction(0), 0.0f, 0.00001f);
//   EXPECT_NEAR(ray.direction(1), 0.0f, 0.00001f);
//   EXPECT_NEAR(ray.direction(2), -1.0f, 0.00001f);

//   // Test 5
//   struct Ray ray2 = RayToPixel(camera4, 0, 0);
//   EXPECT_TRUE(ray2.origin == Point1Dim(0, 0, 0));
//   EXPECT_NEAR(ray2.direction(0), 0.66519f, 0.00001);
//   EXPECT_NEAR(ray2.direction(1), 0.33259f, 0.00001);
//   EXPECT_NEAR(ray2.direction(2), -0.66851f, 0.00001);

//   // Test 6
//   camera4.transform = RotationY(M_PI / 4) * Translation(0, -2, 5);
//   struct Ray ray3 = RayToPixel(camera4, 100, 50);
//   EXPECT_NEAR(ray3.origin(0), 0, 0.0000001);
//   EXPECT_NEAR(ray3.origin(1), 2, 0.0000001);
//   EXPECT_NEAR(ray3.origin(2), -5, 0.000001);
//   EXPECT_NEAR(ray3.direction(0), sqrt(2) / 2.0, 0.00001);
//   EXPECT_NEAR(ray3.direction(1), 0.0f, 0.00001);
//   EXPECT_NEAR(ray3.direction(2), -sqrt(2) / 2.0, 0.00001);
// }
// ;

// TEST(Chapter7Test, RenderFunctionTest) {
//   // Test Rendering image
//   World world;
//   struct Camera camera(11, 11, M_PI / 2.0);
//   //
//   camera.transform = ViewTransformation(Point1Dim(0, 0, -5), Point1Dim(0, 0,
//   0),
//                                         Vector1Dim(0, 1, 0));
//   struct Canvas image(11, 11);
//   Render(camera, world, &image);
//   EXPECT_NEAR((image.canvas[5][5]).r, 0.38066, 0.00001);
//   EXPECT_NEAR((image.canvas[5][5]).g, 0.47583, 0.00001);
//   EXPECT_NEAR((image.canvas[5][5]).b, 0.2855, 0.00001);
// }