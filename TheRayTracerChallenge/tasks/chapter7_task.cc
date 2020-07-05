#include <vector>

void Chapter7Task(std::string canvas_file_path) {
  std::cout << "Debug 1.0" << std::endl;
  // Floor
  struct Sphere floor;
  floor.transform = Scaling(10, 0.01, 10);
  floor.material.rgb_color = Color(1, 0.9, 0.9);
  floor.material.specular = 0.0f;

  // Left wall
  struct Sphere left_wall;
  left_wall.transform = Translation(0, 0, 5) * RotationY(-M_PI / 4.0) *
                        RotationX(M_PI / 2.0) * Scaling(10, 0.01, 10);
  left_wall.material = floor.material;

  // Right Wall
  struct Sphere right_wall;
  right_wall.transform = Translation(0, 0, 5) * RotationY(M_PI / 4.0) *
                         RotationX(M_PI / 2.0) * Scaling(10, 0.01, 10);
  right_wall.material = floor.material;

  // Large sphere
  struct Sphere middle;
  middle.transform = Translation(-0.5, 1, 0.5);
  middle.material.rgb_color = Color(0.1, 1, 0.5);
  middle.material.diffuse = 0.7;
  middle.material.specular = 0.3;

  // Smaller green sphere
  struct Sphere right;
  right.transform = Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5);
  right.material.rgb_color = Color(0.5, 1, 0.1);
  right.material.diffuse = 0.7;
  right.material.specular = 0.3;

  // Smallest sphere
  struct Sphere left;
  left.transform = Translation(-1.5, 0.33, -0.75) * Scaling(0.33, 0.33, 0.33);
  left.material.rgb_color = Color(1, 0.8, 0.1);
  left.material.diffuse = 0.7;
  left.material.specular = 0.3;
  std::cout << "Debug 2.0" << std::endl;

  //
  World world;
  struct PointLight point_light(Color(1, 1, 1), Point1Dim(-10, 10, -10));
  world.light = point_light;
  std::cout << "Debug 3.0" << std::endl;
  world.AddObject(Object(floor));
  world.AddObject(Object(left_wall));
  world.AddObject(Object(right_wall));
  world.AddObject(Object(middle));
  // world.AddObject(Object(right));
  // world.AddObject(Object(left));
  std::cout << "Debug 4.0" << std::endl;
  //
  struct Camera camera(300, 600, M_PI / 3);
  std::cout << "Debug 5.0" << std::endl;
  camera.transform = ViewTransformation(
      Point1Dim(0, 1.5, -5), Point1Dim(0, 1, 0), Vector1Dim(0, 1, 0));
  std::cout << "Debug 6.0" << std::endl;
  struct Canvas canvas(camera.v_size, camera.h_size);
  Render(camera, world, &canvas);
  std::cout << "Debug 7.0" << std::endl;
  CanvasToPPM(canvas, canvas_file_path.c_str());
}
int main(int argc, int argv[]) {
  //
}