#include "TheRayTracerChallenge/chapter3/chapter3.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include "gtest/gtest.h"

TEST(Chapter3Test, TestMatrices) {
  // Matrix creation of shape 4x4

  Eigen::Matrix4f M;
  M << 1.0f, 2.0f, 3.0f, 4.0f, 5.5f, 6.5f, 7.5f, 8.5f, 9.0f, 10.0f, 11.0f,
      12.0f, 13.5f, 14.5f, 15.5f, 16.5f;
  float test = 1.0;
  EXPECT_FLOAT_EQ(M(0, 0), 1.0f);
  EXPECT_FLOAT_EQ(M(0, 1), 2.0f);
  EXPECT_FLOAT_EQ(M(0, 2), 3.0f);
  EXPECT_FLOAT_EQ(M(0, 3), 4.0f);
  EXPECT_FLOAT_EQ(M(1, 0), 5.5f);
  EXPECT_FLOAT_EQ(M(1, 1), 6.5f);
  EXPECT_FLOAT_EQ(M(1, 2), 7.5f);

  // Testing equality of matrices
  Eigen::Matrix2f M1;
  Eigen::Matrix2f M2;
  M1 << 1.0f, 2.0f, 5.0f, 6.0f;
  M2 << 1.0f, 2.0f, 5.0f, 6.0f;
  EXPECT_TRUE(M1 == M2);

  // Mutiplication of matrices
  // Well established feature of eigen
};