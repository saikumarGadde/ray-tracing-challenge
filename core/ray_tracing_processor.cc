#include "core/ray_tracing_processor.h"

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

#include "TheRayTracerChallenge/chapter6/chapter6.h"

int main(int argc, char* argv[]) {
  //
  float canvas_pixels = 1000;
  // Size of the wall
  float wall_size = 7;
  // Wall location on the z axis
  float wall_z = 10;
  // Path of the canvas file
  std::string canvas_file_path = "/Users/gaddekumar/Desktop/wow2.ppm";

  Chapter6Task(canvas_pixels, wall_size, wall_z, canvas_file_path);
}

#include "TheRayTracerChallenge/chapter5/chapter5.h"

//

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

#include "core/ops/world_ops.h"

struct Ray RayToPixel(struct Camera camera, float px, float py) {
  // The offset to the edge of the canvas to the pixel center
  float xoffset = (px + 0.5) * camera.pixel_size;
  float yoffset = (py + 0.5) * camera.pixel_size;
  // The untransformed coordinates of the pixel in world space
  // In this case, the camera is pointing towards the -zaxis
  float world_x = camera.half_width - xoffset;
  float world_y = camera.half_height - yoffset;

  // Using the camera matrix, transform the canvas point and teh origin,
  // and then compute ther ays direction vector
  Eigen::Vector4f pixel_world_coord =
      (camera.transform).inverse() * Point1Dim(world_x, world_y, -1);
  Eigen::Vector4f origin_world_coord =
      (camera.transform).inverse() * Point1Dim(0, 0, 0);
  struct Ray ray(origin_world_coord,
                 Normalization(pixel_world_coord - origin_world_coord));
  return ray;
}

Eigen::Matrix4f ViewTransformation(Eigen::Vector4f from, Eigen::Vector4f to,
                                   Eigen::Vector4f up) {
  Eigen::Vector4f forward = Normalization(to - from);
  // Eigen::Vector4f normalized_up = Normalization(up);

  Eigen::Vector4f left = CrossProduct4f(forward, Normalization(up));
  Eigen::Vector4f true_up = CrossProduct4f(left, forward);
  //
  Eigen::Matrix4f orientation;
  orientation << left(0), left(1), left(2), 0.0f, true_up(0), true_up(1),
      true_up(2), 0.0f, -forward(0), -forward(1), -forward(2), 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f;
  Eigen::Matrix4f transformation_matrix =
      orientation * Translation(-from(0), -from(1), -from(2));
  return transformation_matrix;
}

void Render(struct Camera camera, World world, struct Canvas* canvas) {
  // Uses the camera to render an image of the given world
  std::cout << " H size is : " << camera.h_size
            << " camera v size is :: " << camera.v_size << std::endl;
  //
  std::cout << " Debug 8.0 " << std::endl;
  for (int y = 0; y < camera.v_size; y++) {
    for (int x = 0; x < camera.h_size; x++) {
      struct Ray ray = RayToPixel(camera, x, y);
      Eigen::Vector3f color = ColorAt(world, ray);
      struct RGBColor rgb_color;
      rgb_color.r = color(0);
      rgb_color.g = color(1);
      rgb_color.b = color(2);
      PixelWrite(y, x, rgb_color, canvas);
    }
  }
  std::cout << " Render completed/" << std::endl;
}

// Shade hit function
Eigen::Vector3f ShadeHit(World world, struct Comps comps) {
  return Lighting(comps.object.sphere.material, world.light, comps.point,
                  comps.eyev, comps.normalv);
}

// Color At function
Eigen::Vector3f ColorAt(World& world, struct Ray ray) {
  // Step 1 Intersect World function
  std::vector<struct Intersection*> intersections = IntersectWorld(ray, world);

  // Obtain the hit for the ray
  struct Intersection* hit = Hit(&intersections[0], intersections.size());
  //
  if (hit == nullptr) {
    return Color(0, 0, 0);
  } else {
    struct Comps comps = PrepareComputations(*hit, ray);
    return ShadeHit(world, comps);
  }
}

// Preapare computation
struct Comps PrepareComputations(struct Intersection intersection,
                                 struct Ray ray) {
  struct Comps comps;
  comps.t = intersection.t;
  // Intersection Object
  comps.object = intersection.object;

  comps.point = Position(ray, comps.t);
  comps.eyev = -ray.direction;
  comps.normalv = NormalAt(comps.object.sphere, comps.point);

  if (comps.normalv.dot(comps.eyev) < 0) {
    comps.inside = true;
    comps.normalv = -comps.normalv;
  } else {
    comps.inside = false;
  }
  return comps;
}

// Method to intersect the ray and the world
std::vector<struct Intersection*> IntersectWorld(struct Ray ray, World world) {
  std::vector<struct Intersection*> intersections;
  for (int i = 0; i < world.objects.size(); i++) {
    std::vector<struct Intersection*> intersection =
        Intersect(ray, world.objects[i].sphere);
    for (int j = 0; j < intersection.size(); j++) {
      intersections.push_back(intersection[j]);
    }
  }
  return intersections;
}
