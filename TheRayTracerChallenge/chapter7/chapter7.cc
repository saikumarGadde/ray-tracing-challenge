#include "TheRayTracerChallenge/chapter7/chapter7.h"
#include "TheRayTracerChallenge/chapter2/chapter2.h"

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

// Cross product
Eigen::Vector4f CrossProduct4f(Eigen::Vector4f vector1,
                               Eigen::Vector4f vector2) {
  //

  Eigen::Vector4f cross_product;
  Eigen::Vector3f c1 = vector1.head(3);
  Eigen::Vector3f c2 = vector2.head(3);
  cross_product.head(3) = c1.cross(c2);
  cross_product(3) = 0.0f;
  return cross_product;
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

// Add color to a pixel in canvas
void PixelWrite(int height, int width, struct RGBColor color,
                struct Canvas* canvas) {
  // Assign the color value to the pixel
  canvas->canvas[height][width] = color;
}

// // Count number of digits in an integer
// int NumberOfDigitsInInteger7(int number) {
//   return std::floor(log10(number) + 1);
// }

// Write Pixel To Canvas
void CanvasPPM(struct Canvas* canvas, const char ppm_file_path[]) {
  // Open a PPM file
  FILE* fp = fopen(ppm_file_path, "w");
  // Write header to the PPM File
  std::cout << " Canvas height is :: " << canvas->height
            << " Canvas width si :: " << canvas->width << std::endl;
  fprintf(fp, "P3\n%d %d\n255\n", canvas->height, canvas->width);

  int r;
  int g;
  int b;
  int r_count;
  int g_count;
  int b_count;
  for (int y = 0; y < canvas->height; y++) {
    int count = 0;
    for (int x = 0; x < canvas->width; x++) {
      struct RGBColor pixel_color = canvas->canvas[y][x];
      r = std::max(0, std::min((int)(pixel_color.r * 255), 255));
      g = std::max(0, std::min((int)(pixel_color.g * 255), 255));
      b = std::max(0, std::min((int)(pixel_color.b * 255), 255));
      // r_count = NumberOfDigitsInInteger7(r) + 1;
      // g_count = NumberOfDigitsInInteger7(g) + 1;
      // b_count = NumberOfDigitsInInteger7(b) + 1;
      // Write the r, g, and b values to the PPM File
      // if the length of the line is less than some number, just push it to the
      // next line
      fprintf(fp, " %d ", r);
      fprintf(fp, " %d ", g);
      fprintf(fp, " %d ", b);
      count += 12;
      if (count > 70) {
        fprintf(fp, "\n");
      }
    }
    fprintf(fp, "\n");
  }
  // Close the PPM File
  fclose(fp);
};

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
  struct Camera camera(600, 600, M_PI / 3);
  std::cout << "Debug 5.0" << std::endl;
  camera.transform = ViewTransformation(
      Point1Dim(0, 1.5, -5), Point1Dim(0, 1, 0), Vector1Dim(0, 1, 0));
  std::cout << "Debug 6.0" << std::endl;
  struct Canvas canvas(camera.v_size, camera.h_size);
  Render(camera, world, &canvas);
  std::cout << "Debug 7.0" << std::endl;
  CanvasToPPM(canvas, canvas_file_path.c_str());
}