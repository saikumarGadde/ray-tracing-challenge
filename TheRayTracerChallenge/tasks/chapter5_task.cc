

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

main() {
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