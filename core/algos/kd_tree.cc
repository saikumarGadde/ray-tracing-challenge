#include "core/algos/kd_tree.h"

KDTree::Init(std::vector<Eigen::Vector3d> points) {
  //

  //
}

KDTree::NNSearch() {
  // Nearest Neighbor search of a given point
}

KDTree::Clear() {
  // Clear the KDTree
}

KDTreeNode* KDTree::MakeTree(size_t begin, size_t end, size_t index) {
  if (end <= begin) {
    return nullptr;
  }

  KDTreeNode* root = nullptr;

  //

  return root_node;
}