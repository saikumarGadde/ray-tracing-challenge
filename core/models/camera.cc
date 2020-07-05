#include "core/models/camera.h"

void Camera::PixelSize(float hsize, float vsize, float fieldofview,
                       float* pixelsize, float* halfheight, float* halfwidth) {
  float half_view = tan(fieldofview / 2.0);
  float aspect = hsize / vsize;
  if (aspect >= 1) {
    *halfwidth = half_view;
    *halfheight = half_view / aspect;
  } else {
    *halfwidth = half_view * aspect;
    *halfheight = half_view;
  }
  *pixelsize = ((*halfwidth) * 2) / hsize;
}

void Camera::RayToPixel(float px, float py, Ray* ray) {
  // The offset to the edge of the canvas to the pixel center
  float xoffset = (px + 0.5) * pixel_size_;
  float yoffset = (py + 0.5) * pixel_size_;
  // The untransformed coordinates of the pixel in world space
  // In this case, the camera is pointing towards the -zaxis
  float world_x = half_width_ - xoffset;
  float world_y = half_height_ - yoffset;

  // Using the camera matrix, transform the canvas point and teh origin,
  // and then compute ther ays direction vector
  Eigen::Vector4f pixel_world_coord =
      (transform_).inverse() * Point1Dim(world_x, world_y, -1);
  Eigen::Vector4f origin_world_coord =
      (transform_).inverse() * Point1Dim(0, 0, 0);
  ray->SetOrigin(origin_world_coord);
  ray->SetDirection(Normalization(pixel_world_coord - origin_world_coord));
}

void Camera::SetTransform(Eigen::Matrix4f transform) {
  // Sets transform
  transform_ = transform;
}

Eigen::Matrix4f Camera::GetTransform() {
  // Returns transform matrix
  return transform_;
}

void Camera::SetPixelSize(float pixel_size) {
  // Sets pixel size
  pixel_size_ = pixel_size;
}

float Camera::GetPixelSize() {
  // Returns pixel size
  return pixel_size_;
}