#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/camera.h"
#include "core/models/phong_model.h"
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/models/world.h"
#include "core/ops/color_ops.h"
#include "core/ops/transformations.h"
#include "core/ops/vector_ops.h"
#include "core/visual/canvas.h"
#include "gtest/gtest.h"

TEST(Chapter8Test, Chapter8Task1) {
  // Test 1
  Eigen::Vector4f eyev = Vector1Dim(0, 0, -1);
  Eigen::Vector4f normalv = Vector1Dim(0, 0, -1);
  struct PointLight point_light(RGBColor(1, 1, 1), Point1Dim(0, 0, -10));
  bool in_shadow = true;
  struct Material material;
  Eigen::Vector4f position = Point1Dim(0, 0, 0);
  Eigen::Vector3f color = phong_model::Lighting(material, point_light, position,
                                                eyev, normalv, in_shadow);
  EXPECT_TRUE(color == RGBColor(0.1, 0.1, 0.1));

  // Test 2
  bool default_world = true;
  World world(default_world);
  Eigen::Vector4f point = Point1Dim(0, 10, 0);
  EXPECT_TRUE(phong_model::IsShadowed(world, point) == false);

  // Test 3

  Eigen::Vector4f point2 = Point1Dim(10, -10, 10);
  EXPECT_TRUE(phong_model::IsShadowed(world, point2) == true);

  // Test 4
  Eigen::Vector4f point3 = Point1Dim(-20, 20, -20);
  EXPECT_TRUE(phong_model::IsShadowed(world, point3) == false);

  // Test 5
  Eigen::Vector4f point4 = Point1Dim(-2, 2, -2);
  EXPECT_TRUE(phong_model::IsShadowed(world, point4) == false);
};