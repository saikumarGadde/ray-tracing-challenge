#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/ray.h"
#include "core/ops/vector_ops.h"

// Implementing a Camera
class Camera {
 public:
  Camera(float h_size, float v_size, float field_of_view,
         Eigen::Matrix4f transform = Eigen::Matrix4f::Identity())
      : h_size_(h_size),
        v_size_(v_size),
        field_of_view_(field_of_view),
        transform_(transform) {
    PixelSize(h_size, v_size, field_of_view, &pixel_size_, &half_height_,
              &half_width_);
  };

  // Horizontal size of the canvas that the picture will be rendered to
  float h_size_;
  // Vertical size of the canvas that the picture will be rendered to
  float v_size_;
  // Field of view of the Camera
  float field_of_view_;
  // Transformation describing how the world should be oriented relative to
  // camera
  Eigen::Matrix4f transform_;
  // Set the pixel size on the canvas
  float pixel_size_;
  // Half height of the canvas
  float half_height_;
  // Half Width of the canvas
  float half_width_;

  // Obtain the pixel size of the canvas
  void PixelSize(float hsize, float vsize, float fieldofview, float* pixelsize,
                 float* halfheight, float* halfwidth);

  void RayToPixel(float px, float py, Ray* ray);

  void SetTransform(Eigen::Matrix4f transform);

  Eigen::Matrix4f GetTransform();

  void SetPixelSize(float pixel_size);

  float GetPixelSize();
};
