#include "core/algos/kd_tree.h"

TEST(KDTreeTest, TestPointInsertion) {
  //
  KDtree kd_tree;

  std::vector<Eigen::Vector3f> points;
  points.push_back(Point3D(3.0f, 6.0f, 0.0f));
  points.push_back(Point3D(17.0f, 15.0f, 0.0f));
  points.push_back(Point3D(13.0f, 15.0f, 0.0f));
  points.push_back(Point3D(6.0f, 12.0f, 0.0f));
  points.push_back(Point3D(9.0f, 1.0f, 0.0f));
  points.push_back(Point3D(2.0f, 7.0f, 0.0f));
  points.push_back(Point3D(10.0f, 19.0f, 0.0f));

  kd_tree.Init(points);
}