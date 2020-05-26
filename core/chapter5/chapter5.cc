#include "core/chapter5/chapter5.h"

Eigen::Vector4f Position(const struct Ray ray, const float distance) {
  return ray.origin + (ray.direction * distance);
}

// Mehtod to intersect the ray and sphere
std::vector<struct Intersection*> Intersect(struct Ray ray,
                                            struct Sphere sphere) {
  // Vector from the spheres center to the ray origin
  Eigen::Vector4f sphere_to_ray = ray.origin - sphere.center;
  float a = ray.direction.dot(ray.direction);
  float b = 2 * (ray.direction.dot(sphere_to_ray));
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