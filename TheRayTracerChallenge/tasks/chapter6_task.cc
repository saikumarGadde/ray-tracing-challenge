#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/vector_ops.h"
#include "core/visual/canvas.h"

void Chapter6Task(float canvas_pixels, float wall_size, float wall_z,
                  std::string canvas_file_path) {
  float pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2;

  Canvas canvas(canvas_pixels, canvas_pixels);

  Object sphere_object(object_type::ObjectType::SPHERE);
  sphere_object.GetMaterial().rgb_color = RGBColor(1.0f, 0.2f, 1.0f);
  Eigen::Matrix4f scaling_matrix = Scaling(1, 1, 1);
  sphere_object.SetTransform(scaling_matrix);

  struct PointLight point_light(RGBColor(1.0f, 1.0f, 1.0f),
                                Point1Dim(-10, 10, -10));

  Eigen::Vector4f ray_origin = Point1Dim(0, 0, -5);
  // For each row of pixels in the canvas
  for (int y = 0; y < canvas_pixels; y++) {
    float world_y = half - pixel_size * y;
    for (int x = 0; x < canvas_pixels; x++) {
      float world_x = half - pixel_size * x;
      Eigen::Vector4f point_on_canvas = Point1Dim(world_x, world_y, wall_z);
      Eigen::Vector4f ray_direction = point_on_canvas - ray_origin;
      Ray ray(ray_origin, Normalization(ray_direction));
      ray.IntersectObject(sphere_object);
      struct Intersection* hit = ray.PopIntersection();
      if (hit != nullptr) {
        // @TODO
        Eigen::Vector4f point = ray.Position((*hit).t_);
        Eigen::Vector4f normalv = (*hit).object_->NormalAt(point);
        Eigen::Vector4f eyev = -ray.GetDirection();
        Eigen::Vector3f rgb_color = ray.Lighting2(
            (*hit).object_->GetMaterial(), point_light, point, eyev, normalv);
        canvas.WritePixel(y, x, rgb_color);
      }
    }
  }
  canvas.CanvasToPPM(canvas_file_path.c_str());
}

int main(int argc, char* argv[]) {
  float canvas_pixels = 1000;
  // Size of the wall
  float wall_size = 7;
  // Wall location on the z axis
  float wall_z = 10;
  // Path of the canvas file
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/chapter6.ppm";

  Chapter6Task(canvas_pixels, wall_size, wall_z, canvas_file_path);
}