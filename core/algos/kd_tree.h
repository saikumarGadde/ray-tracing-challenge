#pragma once
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <algorithm>
#include <cmath>

/**
Each box-shaped region is defined by 2k planes, where k is the number of
dimensions. It is a space partitioning data structure for organizing points in
K-Dimensional space. Flavors of kd tree differ in exactly how the splitting
plane is selected.
1. Cycling through the dimensions
2. Cutting along the largest dimension.
3. Quadtrees : Quadtrees seem popular on image data. where the leaf cells
imply that all pixels in the regions have same color
4. kd trees are a special case of binary space partitioning trees.
5. Points are inserted by selecting the median of the points being put into
the subtree, with respect to their coordinates in the axis being used to create
the splitting plane.
6. Balanced kdtrees are not optimal for all the applications.
7. In the case where the median point is not selected, there is no guarantee
that the tree will be balanced.
8. So, instead of selecting the exact median, we can select the median of a
few randomly selected points.
9. There are variant algorithms for constructing the tree. You can use a simple
median strategy. Variants of the nearest neighbor search include nearest
N neighbors, approximate nearest neighbor, and range searches.
10. KDTrees are not always balanced. KD Tree are normally used with a
spatial data.
11. index is the dimension number.
*/

struct KDTreeNode {
  // Node of the

  // Left and Right Nodes
  KDTreeNode* left;
  KDTreeNode* right;
};

Eigen::Vector3f Point3D(float x, float y, float z) {
  Eigen::Vector3f point_3d;
  point_3d << x, y, z;
  return point_3d;
}

class KDTree {
  // Initialize the KD Tree with the vector of points
  bool Init(const std::vector<Eigen::Vector3d> points);

  // Nearest Neighbor search of a given point
  int NNSearch();

  // Clear the kdtree
  bool Clear();

  //
  KDTreeNode* MakeTree(size_t begin, size_t end, size_t index);
}