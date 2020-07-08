#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/material.h"
#include "core/ops/color_ops.h"
#include "core/ops/vector_ops.h"
/* Different types of lighting
1. Ambient lighting: Background lighting, or light reflected from other objects
   in the environment. Phong model treats this as a constant, coloring all
   points on the surface equally.
2. Diffuse reflection: Is light reflected from matte surface. Depends only on
   the angle between the light source and the surface normal.
3. Specular reflection: Reflection of the light source itself,
*/

// Point light struct
struct PointLight {
 public:
  PointLight(Eigen::Vector3f intensity, Eigen::Vector4f point)
      : intensity_(intensity), point_(point) {}

  // Empty constructor
  PointLight() {}

  void SetIntensity(Eigen::Vector3f intensity) {
    // Set intensity of point light
    intensity_ = intensity;
  }
  void SetLightPosition(Eigen::Vector4f point) {
    // Set position of the point light
    point_ = point;
  }

  Eigen::Vector3f GetIntensity() {
    // Return Intensity
    return intensity_;
  }
  Eigen::Vector4f GetLightPosition() {
    // Return Light position
    return point_;
  }

 private:
  // Color
  Eigen::Vector3f intensity_;
  // Position of the light
  Eigen::Vector4f point_;
};
