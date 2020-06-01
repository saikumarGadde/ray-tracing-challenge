#pragma once

// Struct of the Sphere
struct Sphere {
  // Constructor of the Sphere with a center and radius
  Sphere(Eigen::Vector4f center_, float radius_, Eigen::Matrix4f transform_,
         struct Material material_)
      : center(center_),
        radius(radius_),
        transform(transform_),
        material(material_) {}

  Sphere() {
    center << 0.0f, 0.0f, 0.0f, 1.0f;
    radius = 1;
    transform = Eigen::Matrix4f::Identity();
  }
  // Store the center fo the sphere
  Eigen::Vector4f center;
  // Store the radius of the Sphere
  float radius;
  // transform of the sphere object
  Eigen::Matrix4f transform;
  // Material of the object
  struct Material material;
};
