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

float Magnitude(Eigen::Vector4f& vector) {
  return sqrt(vector[0] * vector[0] + vector[1] * vector[1] +
              vector[2] * vector[2]);
}

Eigen::Vector4f Normalization(Eigen::Vector4f vector) {
  Eigen::Vector4f normalized_vector;
  float magnitude = Magnitude(vector);
  normalized_vector[0] = vector[0] / magnitude;
  normalized_vector[1] = vector[1] / magnitude;
  normalized_vector[2] = vector[2] / magnitude;
  normalized_vector[3] = vector[3];
  return normalized_vector;
}

// Putting it together
void Chapter5Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path) {
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2;

  struct Canvas canvas(canvas_pixels, canvas_pixels);
  struct RGBColor rgb_color = {1, 0, 0};
  struct Sphere sphere;
  Eigen::Matrix4f scaling_matrix = Scaling(1, 1, 1);
  sphere.transform = scaling_matrix;

  Eigen::Vector4f ray_origin = Point1Dim(0, 0, -5);
  // For each row of pixels in the canvas
  for (int y = 0; y < canvas_pixels; y++) {
    // Compute the world Y Coordinate
    float world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; x++) {
      float world_x = half - pixel_size * x;

      Eigen::Vector4f point_on_canvas = Point1Dim(world_x, world_y, wall_z);
      Eigen::Vector4f ray_direction = point_on_canvas - ray_origin;
      Eigen::Vector4f normalized_vector = Normalization(ray_direction);
      struct Ray ray(ray_origin, normalized_vector);

      std::vector<struct Intersection*> intersections = Intersect(ray, sphere);
      struct Intersection* hit = Hit(&intersections[0], intersections.size());
      if (hit != nullptr) {
        WritePixel(canvas, y, x, rgb_color);
      }
    }
  }

  CanvasToPPM(canvas, canvas_file_path.c_str());
}