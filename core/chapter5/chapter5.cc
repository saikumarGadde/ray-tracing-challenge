#include "core/chapter5/chapter5.h"

Eigen::Vector4f Position(const struct Ray ray, const float distance) {
  return ray.origin + (ray.direction * distance);
}

// Mehtod to intersect the ray and sphere
std::vector<struct Intersection*> Intersect(struct Ray ray,
                                            struct Sphere sphere) {
  // Transform the ray using the sphere.transform transformation
  Eigen::Matrix4f sphere_transform = sphere.transform;
  Eigen::Matrix4f sphere_transform_inverse = sphere_transform.inverse();
  struct Ray ray2 = Transform(sphere_transform_inverse, ray);
  // Vector from the spheres center to the ray origin
  Eigen::Vector4f sphere_to_ray = ray2.origin - sphere.center;
  float a = ray2.direction.dot(ray2.direction);
  float b = 2 * (ray2.direction.dot(sphere_to_ray));
  float c = sphere_to_ray.dot(sphere_to_ray) - sphere.radius * sphere.radius;
  float discriminant = b * b - 4 * a * c;

  std::vector<struct Intersection*> intersections;
  if (discriminant < 0) {
    return intersections;
  }

  float t1 = (-b + sqrt(discriminant)) / (2 * a);
  float t2 = (-b - sqrt(discriminant)) / (2 * a);
  std::cout << " T1: " << t1 << " T2 :: " << t2 << std::endl;
  // @TODO :: Use unique pointers over here
  struct Intersection* intersection1 = new Intersection(t1, sphere);
  struct Intersection* intersection2 = new Intersection(t2, sphere);

  // struct Intersection intersection1(t1, sphere);
  // struct Intersection intersection2(t2, sphere);
  if (t1 < t2) {
    intersections.push_back(intersection1);
    intersections.push_back(intersection2);
  } else {
    intersections.push_back(intersection2);
    intersections.push_back(intersection1);
  }
  return intersections;
}

struct Intersection* Hit(struct Intersection* intersections[], int size) {
  // Have to sort the intersections over here
  float min_value = std::numeric_limits<float>::max();
  struct Intersection* result = nullptr;
  for (int i = 0; i < size; i++) {
    if (intersections[i]->t < 0) {
      continue;
    } else {
      if (intersections[i]->t < min_value) {
        min_value = intersections[i]->t;
        result = intersections[i];
      }
    }
  }
  return result;
}

// Transformation with a transformation matrix and vector or ray
struct Ray Transform(Eigen::Matrix4f& transform_matrix, struct Ray ray) {
  Eigen::Vector4f transformed_origin = transform_matrix * ray.origin;
  Eigen::Vector4f transformed_direction = transform_matrix * ray.direction;
  struct Ray transformed_ray(transformed_origin, transformed_direction);
  return transformed_ray;
}