#include "core/chapter6/chapter6.h"
#include <math.h>
#include <cmath>
#include <iostream>
#include "core/chapter5/chapter5.h"

Eigen::Vector4f NormalAt(struct Sphere sphere, Eigen::Vector4f& point) {
  // @TODO
  Eigen::Vector4f normal_vector = point - sphere.center;
  normal_vector = Normalization(normal_vector);
  return normal_vector;
}

Eigen::Vector4f NormalAtWorldPoint(struct Sphere sphere,
                                   Eigen::Vector4f& world_point) {
  // Obtain the normal in the object space
  Eigen::Vector4f object_point = (sphere.transform).inverse() * world_point;
  Eigen::Vector4f object_normal = object_point - sphere.center;

  // Transform the normal in the object space to the world space
  Eigen::Vector4f world_normal =
      ((sphere.transform).inverse()).transpose() * object_normal;
  world_normal[3] = 0;
  world_normal = Normalization(world_normal);
  // Return the normalized normal of the sphere
  return world_normal;
}

Eigen::Vector4f Reflect(Eigen::Vector4f in, Eigen::Vector4f normal) {
  // @
  Eigen::Vector4f reflection = in - (normal * 2 * in.dot(normal));
  return reflection;
}

Eigen::Vector3f RGBColorSum(Eigen::Vector3f color1, Eigen::Vector3f color2) {
  Eigen::Vector3f color;
  color(0) = std::min(1.0f, color1(0) + color2(0));
  color(1) = std::min(1.0f, color1(1) + color2(1));
  color(2) = std::min(1.0f, color1(2) + color2(2));
  return color;
}

Eigen::Vector3f RGBColorMultiply(Eigen::Vector3f color1,
                                 Eigen::Vector3f color2) {
  Eigen::Vector3f color;
  color(0) = color1(0) * color2(0);
  color(1) = color1(1) * color2(1);
  color(2) = color1(2) * color2(2);
  return color;
}

Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv) {
  // Combine the surface color with the lights color/intensity
  Eigen::Vector3f effective_color =
      RGBColorMultiply(material.rgb_color, point_light.intensity);

  // Find the direction of the color source
  Eigen::Vector4f lightv = Normalization(point_light.point - position);

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
      specular = point_light.intensity * material.specular * factor;
    }
  }

  return ambient + diffuse + specular;
}

// Creating color
Eigen::Vector3f Color(float r, float g, float b) {
  Eigen::Vector3f color;
  color(0) = r;
  color(1) = g;
  color(2) = b;
  return color;
}

void Chapter6Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path) {
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2;

  struct Canvas canvas(canvas_pixels, canvas_pixels);
  struct RGBColor rgb_color = {1, 0, 0};
  struct Sphere sphere;
  sphere.material.rgb_color = Color(1.0f, 0.2f, 1.0f);
  Eigen::Matrix4f scaling_matrix = Scaling(1, 1, 1);
  sphere.transform = scaling_matrix;

  //
  struct PointLight point_light(Color(1.0f, 1.0f, 1.0f),
                                Point1Dim(-10, 10, -10));

  Eigen::Vector4f ray_origin = Point1Dim(0, 0, -5);
  // For each row of pixels in the canvas
  for (int y = 0; y < canvas_pixels; y++) {
    float world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; x++) {
      float world_x = half - pixel_size * x;

      Eigen::Vector4f point_on_canvas = Point1Dim(world_x, world_y, wall_z);
      Eigen::Vector4f ray_direction = point_on_canvas - ray_origin;
      struct Ray ray(ray_origin, Normalization(ray_direction));

      std::vector<struct Intersection*> intersections = Intersect(ray, sphere);
      struct Intersection* hit = Hit(&intersections[0], intersections.size());
      if (hit != nullptr) {
        // @TODO
        Eigen::Vector4f point = Position(ray, hit->t);
        Eigen::Vector4f normalv = NormalAt(hit->sphere, point);
        Eigen::Vector4f eyev = -ray.direction;
        Eigen::Vector3f color =
            Lighting((*hit).sphere.material, point_light, point, eyev, normalv);
        struct RGBColor rgb_color = {color(0), color(1), color(2)};
        WritePixel(canvas, y, x, rgb_color);
      }
    }
  }
  CanvasToPPM(canvas, canvas_file_path.c_str());
}