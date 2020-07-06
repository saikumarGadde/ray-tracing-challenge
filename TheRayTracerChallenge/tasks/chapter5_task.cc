#include "core/models/light.h"
#include "core/models/object.h"
#include "core/models/object_type.h"
#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/vector_ops.h"
#include "core/visual/canvas.h"

// Putting it together
void Chapter5Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path) {
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2;

  Canvas canvas(canvas_pixels, canvas_pixels);
  Eigen::Vector3f rgb_color = RGBColor(1, 0, 0);

  Object sphere_object(object_type::ObjectType::SPHERE);
  sphere_object.SetTransform(Scaling(1, 1, 1));

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
      Ray ray(ray_origin, normalized_vector);
      ray.IntersectObject(sphere_object);
      struct Intersection* hit = ray.PopIntersection();
      if (hit != nullptr) {
        canvas.WritePixel(y, x, rgb_color);
      }
    }
  }
  canvas.CanvasToPPM(canvas_file_path.c_str());
}

int main(int argc, char* argv[]) {
  // Number of pixels in the canvas
  float canvas_pixels = 100;
  // Size of the wall
  float wall_size = 7;
  // Wall location on the z axis
  float wall_z = 10;
  // Path of the canvas file
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/wow.ppm";

  Chapter5Task(canvas_pixels, wall_size, wall_z, canvas_file_path);
}