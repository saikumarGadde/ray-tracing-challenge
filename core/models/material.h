#pragma once
#include <Eigen/Core>
#include <Eigen/Dense>
#include <cmath>

struct StripePattern {
  // StripePattern constructor in C++
  StripePattern(Eigen::Vector3f a, Eigen::Vector3f b) : a_(a), b_(b) {
    //

    //
  }

  Eigen::Vector3f StripeAt(Eigen::Vector4f point) {
    if ((int)floor(point[0]) % 2 == 0) {
      return a_;
    } else {
      return b_;
    }
  }

  Eigen::Vector3f a_;
  Eigen::Vector3f b_;
};

// Material struct
struct Material {
  Material(Eigen::Vector3f rgb_color_, float ambient_, float diffuse_,
           float specular_, float shininess_)
      : rgb_color(rgb_color_),
        ambient(ambient_),
        diffuse(diffuse_),
        specular(specular_),
        shininess(shininess_) {}

  Material() {
    rgb_color(0) = 1;
    rgb_color(1) = 1;
    rgb_color(2) = 1;
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
  }

  Eigen::Vector3f rgb_color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
};
