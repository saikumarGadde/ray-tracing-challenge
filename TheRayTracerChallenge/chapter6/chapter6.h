#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include "TheRayTracerChallenge/chapter5/chapter5.h"
#include "core/protos/visualization_utils.h"

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
  PointLight(Eigen::Vector3f intensity_, Eigen::Vector4f point_)
      : intensity(intensity_), point(point_) {}
  PointLight() {}
  // Color
  Eigen::Vector3f intensity;
  // Position of the light
  Eigen::Vector4f point;
};

// Normat at NormalAt
Eigen::Vector4f NormalAt(struct Sphere sphere, Eigen::Vector4f& point);

// Normal at NormalAtWorldPoint
Eigen::Vector4f NormalAtWorldPoint(struct Sphere sphere,
                                   Eigen::Vector4f& world_point);

// Calculation of the reflection
Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal);

// Lighting function
Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f eye_position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv);

// Sum of two RGB Colors
Eigen::Vector3f RGBColorSum(Eigen::Vector3f color1, Eigen::Vector3f color2);

// Multiplication of two RGB Colors
Eigen::Vector3f RGBColorMultiply(Eigen::Vector3f color1,
                                 Eigen::Vector3f color2);

// Putting it together
void Chapter6Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path);

// Creating color
Eigen::Vector3f Color(float r, float g, float b);
