#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include "core/models/light.h"
#include "core/models/ray.h"

namespace phong_model {

// Reflection of the ray
Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal);

// Lighting function
Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv, bool in_shadow = false);

bool IsShadowed(World& world, Eigen::Vector4f point);

}  // namespace phong_model