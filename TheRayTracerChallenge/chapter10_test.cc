#include <gflags/gflags.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/material.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "gtest/gtest.h"

TEST(Chapter10Test, Chapter10Task1) {
  // Test 1
  Eigen::Vector3f black = RGBColor(0, 0, 0);
  Eigen::Vector3f white = RGBColor(1, 1, 1);
  StripePattern stripe_pattern{white, black};
  EXPECT_TRUE(stripe_pattern.a_ == white);
  EXPECT_TRUE(stripe_pattern.b_ == black);

  EXPECT_TRUE(stripe_pattern.StripeAt(Point1Dim(0, 0, 0)) == white);
  EXPECT_TRUE(stripe_pattern.StripeAt(Point1Dim(0, 1, 0)) == white);
  EXPECT_TRUE(stripe_pattern.StripeAt(Point1Dim(0, 2, 0)) == white);
};