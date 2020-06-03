#include "TheRayTracerChallenge/chapter7/chapter7.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include "gtest/gtest.h"

TEST(Chapter7Test, TestWorld) {
  // TEST 1
  World world;

  // TEST 2
  struct Ray ray(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  std::vector<struct Intersection*> intersections = Intersect(ray, world);
  EXPECT_EQ(intersections.size(), 4);
  std::cout << "0: " << intersections[0]->t << "1: " << intersections[1]->t
            << "2: " << intersections[2]->t << "1: " << intersections[3]->t
            << std::endl;
  EXPECT_EQ(intersections[0]->t, 4.5f);  // 4.5f
  EXPECT_EQ(intersections[1]->t, 5.5f);  // 5.5f
  EXPECT_EQ(intersections[2]->t, 4.0f);  // 4.0f
  EXPECT_EQ(intersections[3]->t, 6.0f);

  // Test 2
  struct Sphere shape;

  struct Intersection i(4, Object(shape));
  struct Comps comps = PrepareComputations(i, ray);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, -1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == false);

  // Test 3
  struct Ray ray2(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct Intersection i2(1, Object(shape));
  comps = PrepareComputations(i2, ray2);
  EXPECT_EQ(comps.point, Point1Dim(0, 0, 1));
  EXPECT_EQ(comps.eyev, Vector1Dim(0, 0, -1));
  EXPECT_EQ(comps.normalv, Vector1Dim(0, 0, -1));
  EXPECT_TRUE(comps.inside == true);

  // // TEST 4
  struct Ray ray4(Point1Dim(0, 0, -5), Vector1Dim(0, 0, 1));
  struct Intersection i4(4, world.objects[1]);
  comps = PrepareComputations(i4, ray4);
  Eigen::Vector3f c = ShadeHit(world, comps);
  EXPECT_NEAR(c(0), 0.38066, 0.00001);
  EXPECT_NEAR(c(1), 0.47583, 0.00001);
  EXPECT_NEAR(c(2), 0.2855, 0.0001);

  // Test 5
  struct Ray ray5(Point1Dim(0, 0, 0), Vector1Dim(0, 0, 1));
  struct PointLight point_light(Color(1, 1, 1), Point1Dim(0, 0.25, 0));
  world.light = point_light;
  struct Intersection i5(0.5, world.objects[0]);
  comps = PrepareComputations(i5, ray5);
  Eigen::Vector3f c2 = ShadeHit(world, comps);
  EXPECT_NEAR(c2(0), 0.90498, 0.00001);
  EXPECT_NEAR(c2(1), 0.90498, 0.00001);
  EXPECT_NEAR(c2(2), 0.90498, 0.0001);
};