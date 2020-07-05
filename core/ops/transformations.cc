#include "core/ops/transformations.h"

Eigen::Matrix4f Translation(float x, float y, float z) {
  Eigen::Matrix4f translation_matrix = Eigen::Matrix4f::Identity();
  translation_matrix(0, 3) = x;
  translation_matrix(1, 3) = y;
  translation_matrix(2, 3) = z;
  return translation_matrix;
}

Eigen::Matrix4f Scaling(float x, float y, float z) {
  Eigen::Matrix4f scaling_matrix = Eigen::Matrix4f::Identity();
  scaling_matrix(0, 0) = x;
  scaling_matrix(1, 1) = y;
  scaling_matrix(2, 2) = z;
  return scaling_matrix;
}

Eigen::Matrix4f RotationX(float radians) {
  Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity();
  rotation_matrix(1, 1) = cos(radians);
  rotation_matrix(1, 2) = -sin(radians);
  rotation_matrix(2, 1) = sin(radians);
  rotation_matrix(2, 2) = cos(radians);
  return rotation_matrix;
}

// Rotation along the Y Axis
Eigen::Matrix4f RotationY(float radians) {
  Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity();
  rotation_matrix(0, 0) = cos(radians);
  rotation_matrix(0, 2) = sin(radians);
  rotation_matrix(2, 0) = -sin(radians);
  rotation_matrix(2, 2) = cos(radians);
  return rotation_matrix;
}

Eigen::Matrix4f RotationZ(float radians) {
  Eigen::Matrix4f rotation_matrix = Eigen::Matrix4f::Identity();
  rotation_matrix(0, 0) = cos(radians);
  rotation_matrix(0, 1) = -sin(radians);
  rotation_matrix(1, 0) = sin(radians);
  rotation_matrix(1, 1) = cos(radians);
  return rotation_matrix;
}

Eigen::Matrix4f Shearing(float x_y, float x_z, float y_x, float y_z, float z_x,
                         float z_y) {
  Eigen::Matrix4f shearing_matrix = Eigen::Matrix4f::Identity();
  shearing_matrix(0, 1) = x_y;
  shearing_matrix(0, 2) = x_z;
  shearing_matrix(1, 0) = y_x;
  shearing_matrix(1, 2) = y_z;
  shearing_matrix(2, 0) = z_x;
  shearing_matrix(2, 1) = z_y;
  return shearing_matrix;
}

Eigen::Matrix4f ViewTransformation(Eigen::Vector4f from, Eigen::Vector4f to,
                                   Eigen::Vector4f up) {
  Eigen::Vector4f forward = Normalization(to - from);
  // Eigen::Vector4f normalized_up = Normalization(up);

  Eigen::Vector4f left = CrossProduct4f(forward, Normalization(up));
  Eigen::Vector4f true_up = CrossProduct4f(left, forward);
  //
  Eigen::Matrix4f orientation;
  orientation << left(0), left(1), left(2), 0.0f, true_up(0), true_up(1),
      true_up(2), 0.0f, -forward(0), -forward(1), -forward(2), 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f;
  Eigen::Matrix4f transformation_matrix =
      orientation * Translation(-from(0), -from(1), -from(2));
  return transformation_matrix;
}