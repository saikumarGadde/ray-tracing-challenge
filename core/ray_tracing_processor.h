#pragma once

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
        Eigen::Vector4f normalv = NormalAt((*hit).object.sphere, point);
        Eigen::Vector4f eyev = -ray.direction;
        Eigen::Vector3f color = Lighting((*hit).object.sphere.material,
                                         point_light, point, eyev, normalv);
        struct RGBColor rgb_color = {color(0), color(1), color(2)};
        WritePixel(canvas, y, x, rgb_color);
      }
    }
  }
  CanvasToPPM(canvas, canvas_file_path.c_str());
}

struct Comps {
  // Object of intersection
  struct Object object;
  // Intersection at a distance
  float t;
  // Precomputations
  Eigen::Vector4f point;
  // Eye vector
  Eigen::Vector4f eyev;
  // Normal Vecotr to the plane
  Eigen::Vector4f normalv;
  // The light is Inside the object or outside the object
  bool inside;
};

// Prepare computations
struct Comps PrepareComputations(struct Intersection intersection,
                                 struct Ray ray);

// Shade hit function
Eigen::Vector3f ShadeHit(World world, struct Comps comps);

// Returns the color ar an intersection point of the ray and the world
Eigen::Vector3f ColorAt(World& world, struct Ray ray);

// Transformation matrix for the camera
Eigen::Matrix4f ViewTransformation(Eigen::Vector4f from, Eigen::Vector4f to,
                                   Eigen::Vector4f up);

// Method to intersect the ray and the world
std::vector<struct Intersection*> IntersectWorld(struct Ray ray, World world);

// Lighting function
Eigen::Vector3f Lighting(struct Material material,
                         struct PointLight point_light,
                         Eigen::Vector4f eye_position, Eigen::Vector4f eyev,
                         Eigen::Vector4f normalv);

// Ray for Pixel
struct Ray RayToPixel(struct Camera camera, float px, float py);

// Render the world form camera
void Render(struct Camera camera, World world, struct Canvas* canvas);

// Chapter7Task
void Chapter7Task(std::string canvas_file_path);

void PixelWrite(int height, int width, struct RGBColor color,
                struct Canvas* canvas);

void CanvasPPM(struct Canvas* canvas, const char ppm_file_path[]);
