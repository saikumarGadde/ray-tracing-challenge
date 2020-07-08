#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/ray.h"
#include "core/ops/vector_ops.h"

// Implementing a Camera
class Camera {
 public:
  Camera(float height, float width, float field_of_view,
         Eigen::Matrix4f transform = Eigen::Matrix4f::Identity())
      : height_(height),
        width_(width),
        field_of_view_(field_of_view),
        transform_(transform) {
    float half_view = tan(field_of_view / 2.0);
    float aspect = width / height;
    if (aspect >= 1) {
      half_width_ = half_view;
      half_height_ = half_view / aspect;
    } else {
      half_width_ = half_view * aspect;
      half_height_ = half_view;
    }
    pixel_size_ = ((half_width_)*2) / width;
  };

  // Obtain the pixel size of the canvas
  void PixelSize(float height, float width, float fieldofview, float* pixelsize,
                 float* halfheight, float* halfwidth);

  void RayToPixel(float px, float py, Ray* ray);

  void SetTransform(Eigen::Matrix4f transform);

  Eigen::Matrix4f GetTransform();

  void SetPixelSize(float pixel_size);

  // Getters
  float GetPixelSize() { return pixel_size_; };
  float GetFieldOfView() { return field_of_view_; }
  float GetWidth() { return width_; };
  float GetHeight() { return height_; };

 private:
  // Horizontal size of the canvas that the picture will be rendered to
  float height_;
  // Vertical size of the canvas that the picture will be rendered to
  float width_;
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
};
