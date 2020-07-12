#include "core/models/ray.h"
#include "core/models/vector.h"
#include "core/ops/color_ops.h"
#include "core/ops/vector_ops.h"
#include "core/ray_tracing_processor.h"
#include "core/visual/canvas.h"

void Chapter9Task(std::string canvas_file_path) {
  // Floor
  Object floor(object_type::ObjectType::PLANE);
  Object back_wall(object_type::ObjectType::PLANE);
  back_wall.SetTransform(Translation(0, 0, 10) * RotationX(-M_PI / 2.0));
  // back_wall.SetTransform(Translation(0, 0, 5) * RotationY(-M_PI / 4.0) *
  //                        RotationX(M_PI / 2.0));
  back_wall.GetMaterial().rgb_color(0) = 0.6;
  back_wall.GetMaterial().rgb_color(1) = 0.2;
  back_wall.GetMaterial().rgb_color(2) = 0.3;

  // Left wall
  Object left_wall(object_type::ObjectType::SPHERE);
  left_wall.SetTransform(Translation(0, 0, 5) * RotationY(-M_PI / 4.0) *
                         RotationX(M_PI / 2.0) * Scaling(10, 0.01, 10));
  left_wall.GetMaterial().rgb_color = RGBColor(1, 0.9, 0.9);
  left_wall.GetMaterial().specular = 0.0f;

  // Right Wall
  Object right_wall(object_type::ObjectType::SPHERE);
  right_wall.SetTransform(Translation(0, 0, 5) * RotationY(M_PI / 4.0) *
                          RotationX(M_PI / 2.0) * Scaling(10, 0.01, 10));
  right_wall.GetMaterial().rgb_color = RGBColor(1, 0.9, 0.9);
  right_wall.GetMaterial().specular = 0.0f;

  // Large sphere
  Object sphere1(object_type::ObjectType::SPHERE);
  sphere1.SetTransform(Translation(-0.5, 1, 0.5));
  sphere1.GetMaterial().rgb_color = RGBColor(0.1, 1, 0.5);
  sphere1.GetMaterial().diffuse = 0.7;
  sphere1.GetMaterial().specular = 0.3;

  // Smaller green sphere
  Object sphere2(object_type::ObjectType::SPHERE);
  sphere2.SetTransform(Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5));
  sphere2.GetMaterial().rgb_color = RGBColor(0.5, 1, 0.1);
  sphere2.GetMaterial().diffuse = 0.7;
  sphere2.GetMaterial().specular = 0.3;

  // Smallest sphere
  Object sphere3(object_type::ObjectType::SPHERE);
  sphere3.SetTransform(Translation(-1.5, 0.33, -0.75) *
                       Scaling(0.33, 0.33, 0.33));
  sphere3.GetMaterial().rgb_color = RGBColor(1, 0.8, 0.1);
  sphere3.GetMaterial().diffuse = 0.7;
  sphere3.GetMaterial().specular = 0.3;

  // Add world and different objects.
  World world(false);
  struct PointLight point_light(RGBColor(1, 1, 1), Point1Dim(-10, 10, -10));
  world.AddLight(point_light);
  world.AddObject(floor);
  world.AddObject(back_wall);
  // world.AddObject(left_wall);
  // world.AddObject(right_wall);
  world.AddObject(sphere1);
  world.AddObject(sphere2);
  world.AddObject(sphere3);

  Camera camera(600, 900, M_PI / 3.0);
  camera.SetTransform(ViewTransformation(
      Point1Dim(0, 1.5, -5), Point1Dim(0, 1, 0), Vector1Dim(0, 1, 0)));
  Canvas canvas(camera.GetHeight(), camera.GetWidth());
  Render(camera, world, &canvas);
  canvas.CanvasToPPM(canvas_file_path.c_str());
}

int main(int argc, char* argv[]) {
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/chapter9.ppm";
  Chapter9Task(canvas_file_path);
}
