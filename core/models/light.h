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

Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal) {
  // @
  Eigen::Vector4f reflection = in - (normal * 2 * in.dot(normal));
  return reflection;
}

Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv) {
  // Combine the surface color with the lights color/intensity
  Eigen::Vector3f effective_color =
      RGBColorMultiply(material.rgb_color, point_light.GetIntensity());

  // Find the direction of the color source
  Eigen::Vector4f lightv =
      Normalization(point_light.GetLightPosition() - position);

  // Compute the ambient contribution
  Eigen::Vector3f ambient = effective_color * material.ambient;

  // light_dot_normal
  Eigen::Vector3f diffuse;
  Eigen::Vector3f specular;
  float light_dot_normal = lightv.dot(normalv);
  if (light_dot_normal < 0) {
    diffuse = Eigen::Vector3f::Zero();
    specular = Eigen::Vector3f::Zero();
  } else {
    // Diffuse contribution
    diffuse = effective_color * material.diffuse * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the light
    // reflects away from the eye
    Eigen::Vector4f reflectv = Reflect(-lightv, normalv);
    float reflect_dot_eye = reflectv.dot(eyev);
    if (reflect_dot_eye <= 0) {
      specular = Eigen::Vector3f::Zero();
    } else {
      float factor = pow(reflect_dot_eye, material.shininess);
      specular = point_light.GetIntensity() * material.specular * factor;
    }
  }
  return ambient + diffuse + specular;
}

// Calculation of the reflection
Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal);
