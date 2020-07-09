#include "core/models/phong_model.h"

namespace phong_model {

// Lighting function
Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal) {
  // @
  Eigen::Vector4f reflection = in - (normal * 2 * in.dot(normal));
  return reflection;
}

//
Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv, bool in_shadow) {
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
  if (in_shadow == true) {
    return ambient;
  }
  return ambient + diffuse + specular;
}

bool IsShadowed(World& world, Eigen::Vector4f point) {
  //
  Eigen::Vector4f v = world.GetLight().GetLightPosition() - point;
  float distance = v.norm();
  Eigen::Vector4f direction = Normalization(v);

  // Obtain a ray from the point of intersection to the light in World
  Ray ray(point, direction);
  ray.IntersectWorld(world);

  struct Intersection* hit = ray.PopIntersection();
  if ((hit != nullptr) && (hit->GetT() < distance)) {
    return true;
  }
  return false;
}

}  // namespace phong_model