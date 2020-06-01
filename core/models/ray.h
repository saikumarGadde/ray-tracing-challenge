

struct Ray {
  Ray(Eigen::Vector4f origin_, Eigen::Vector4f direction_)
      : origin(origin_), direction(direction_) {}
  // Store the origin, which is the starting point of the ray
  Eigen::Vector4f origin;
  // Store the vector, direction in which the ray points to
  Eigen::Vector4f direction;
};

// Material struct
struct Material {
  Material(Eigen::Vector3f rgb_color_, float ambient_, float diffuse_,
           float specular_, float shininess_)
      : rgb_color(rgb_color_),
        ambient(ambient_),
        diffuse(diffuse_),
        specular(specular_),
        shininess(shininess_) {}

  Material() {
    rgb_color(0) = 1;
    rgb_color(1) = 1;
    rgb_color(2) = 1;
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
  }

  Eigen::Vector3f rgb_color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;
};
